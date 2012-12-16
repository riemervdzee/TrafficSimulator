#include "CSimulationView.h"
#include "CSimulationController.h"
#include "CSimulationModel.h"

#include <GL/glfw.h>
#include <cmath>

using namespace wmath;

CSimulationView::CSimulationView(int width, int height)
{
    this->width = width;
    this->height = height;

    // middle of the screen
    mMidX = width / 2;
    mMidY = height / 2;
}

void CSimulationView::Dispose()
{
    mSkybox.Dispose();
    mScene.Dispose();
    traShader.Dispose();
    parShader.Dispose();
    traVertexBuffer.Dispose();
    parVertexBuffer.Dispose();
}

void CSimulationView::Init()
{
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CCW);
    glCullFace(GL_BACK);
    glEnable(GL_TEXTURE_2D);

    mMoveSpeed = 64.0f;
    glfwSetMousePos(mMidX, mMidY);
    glfwDisable( GLFW_MOUSE_CURSOR );
    mMouseSensitivity = 8.0f;

    // init camera
    mCamera.Perspective(60.0f, (float)width / (float)height, 1.f, 400.0f);
    mCamera.LookAt(Vec3(32, 64, -32), Vec3(0, 32.0f, 1), Vec3(0, 1, 0));

    // create skybox
    mSkybox.Init("Data/Textures/miramar", &mCamera);

    // load the scene           
    if( !mScene.Load("Data/crossroad.3dw", trafficLights, waypoints) )                          
        std::cout << "Could not load the scene" << std::endl;

    // load shader for participant
    std::string dvertex;
    std::string dfragment;

    // creating shaders
    LoadTextFile("Data/Shaders/tra_col.vert", dvertex);
    LoadTextFile("Data/Shaders/tra_col.frag", dfragment);

    // load shaders
    parShader.CreateProgram(dvertex, dfragment);
    traShader.CreateProgram(dvertex, dfragment);

    // create buffer for participants
    parVertexBuffer.Create(sizeof(dCube) * 256, GL_DYNAMIC_DRAW);
    traVertexBuffer.Create(sizeof(dCube) * trafficLights.size() * 2, GL_DYNAMIC_DRAW);
}

void CSimulationView::Update(float dt)
{
    // SHUTDOWN SIMULATION
    if( glfwGetKey( GLFW_KEY_ESC ) == GLFW_PRESS  )
    {
        if(mController >= 0)
            mController->SetRunning(false);
    }
    
    static bool lastC = false; /// LAZY HACK!
    if( glfwGetKey( 'C') == GLFW_PRESS) lastC = true;
    if( glfwGetKey( 'C') == GLFW_RELEASE && lastC == true)
    {
        mController->ConnectToNetwork();
        lastC = false;
    }

    int speed = mMoveSpeed;

    // debug
    static bool last = false; // lazy HACK! :P
    if( glfwGetKey( 'L') == GLFW_PRESS) last = true;
    if( glfwGetKey( 'L') == GLFW_RELEASE && last == true)
	{
		mScene.ToggleDebug();
		last = false;
	}

    // PRESS SHIFT FOR SPEED UP
	if( glfwGetKey( GLFW_KEY_LSHIFT ) == GLFW_PRESS)
	{
		speed = mMoveSpeed * 4.0f;
	}

    // ########## CAMERA MOUSE MOVEMENT ###########
    int mX, mY;
    int mdX, mdY;
	glfwGetMousePos(&mX, &mY);
	glfwSetMousePos(width / 2, height / 2);

	mdX = mX - mMidX;
	mdY = mY - mMidY;

    mCamera.Rotate(static_cast<float>(mdY) * dt * mMouseSensitivity, static_cast<float>(mdX) * dt * mMouseSensitivity, 0.0f);
    // ########## END CAMERA MOUSE MOVEMENT ###########

    // ########## CAMERA KEYBOARD MOVEMENT ###########
	if(glfwGetKey( 'S' ) == GLFW_PRESS)
	{
		mCamera.Move(-speed * dt);
	}
	else if(glfwGetKey( 'W' ) == GLFW_PRESS)
	{
		mCamera.Move(speed * dt);
	}

	// strafe camera
	if(glfwGetKey( 'A' ) == GLFW_PRESS)
	{
		mCamera.Strafe(-speed * dt);
	}
	else if(glfwGetKey( 'D' ) == GLFW_PRESS)
	{
		mCamera.Strafe(speed * dt);
	}
	// ########## END CAMERA KEYBOARD MOVEMENT ###########
}

wmath::Vec3 CreateColor(const wmath::Vec3& p1,const wmath::Vec3& p2,
        const wmath::Vec3& p3, wmath::Vec3& color)
{
    static wmath::Vec3 dirLight(-0.5f, 0.5f, 1.0f);
    static wmath::Vec3 ambient(64.0/255.0f, 64.0/255.0f, 64.0/255.0f);
    dirLight.Norm();
    
    // get 2 edges
    wmath::Vec3 A = p3 - p1;
    wmath::Vec3 B = p2 - p1;
    
    // create triangle normal
    wmath::Vec3 norm = A.Cross(B); norm.Norm();
    
    // create color
    float dot = norm * dirLight;
    float diffStrength = (dot < 0.0f)? 0.0f: dot;
    wmath::Vec3 outcolor = (color * diffStrength) + color;
    return outcolor;
}

void CSimulationView::addCube(dCube& cube, wmath::Vec3 pos, 
        float w, float h, float d, wmath::Vec3 color, float rotation, Vec3 extr)
{     
    wmath::Vec3 useColor;
    
    // FRONT
    cube.verts[0].position = Vec3(-0.5f * w, -0.5f * h, -0.5f * d);
    cube.verts[1].position = Vec3(0.5f * w, -0.5f * h, -0.5f * d);
    cube.verts[2].position = Vec3(0.5f * w, 0.5f * h, -0.5f * d);
    
    // set color for this triangle
    useColor = CreateColor(cube.verts[0].position, cube.verts[1].position,
            cube.verts[2].position, color);
    cube.verts[0].color = cube.verts[1].color = cube.verts[2].color = useColor;
    
    cube.verts[3].position = Vec3(-0.5f * w, -0.5f * h, -0.5f * d);
    cube.verts[4].position = Vec3(0.5f * w, 0.5f * h, -0.5f * d);
    cube.verts[5].position = Vec3(-0.5f * w, 0.5f * h, -0.5f * d);
    
    cube.verts[3].color = cube.verts[4].color = cube.verts[5].color = useColor;
    
    // BACK
    cube.verts[6].position = Vec3(0.5f * w, -0.5f * h, 0.5f * d);
    cube.verts[7].position = Vec3(-0.5f * w, -0.5f * h, 0.5f * d);
    cube.verts[8].position = Vec3(-0.5f * w, 0.5f * h, 0.5f * d);
    
    // set color for this triangle
    useColor = CreateColor(cube.verts[6].position, cube.verts[7].position,
            cube.verts[8].position, color);
    cube.verts[6].color = cube.verts[7].color = cube.verts[8].color = useColor;
    
    cube.verts[9].position = Vec3(0.5f * w, -0.5f * h, 0.5f * d);
    cube.verts[10].position = Vec3(-0.5f * w, 0.5f * h, 0.5f * d);
    cube.verts[11].position = Vec3(0.5f * w, 0.5f * h, 0.5f * d);
    
    cube.verts[9].color = cube.verts[10].color = cube.verts[11].color = useColor;
    
    // LEFT
    cube.verts[12].position = Vec3(-0.5f * w, -0.5f * h, 0.5f * d);
    cube.verts[13].position = Vec3(-0.5f * w, -0.5f * h, -0.5f * d);
    cube.verts[14].position = Vec3(-0.5f * w, 0.5f * h, -0.5f * d);
    
    // set color for this triangle
    useColor = CreateColor(cube.verts[12].position, cube.verts[13].position,
            cube.verts[14].position, color);
    cube.verts[12].color = cube.verts[13].color = cube.verts[14].color = useColor;
    
    cube.verts[15].position = Vec3(-0.5f * w, -0.5f * h, 0.5f * d);
    cube.verts[16].position = Vec3(-0.5f * w, 0.5f * h, -0.5f * d);
    cube.verts[17].position = Vec3(-0.5f * w, 0.5f * h, 0.5f * d);
    
    cube.verts[15].color = cube.verts[16].color = cube.verts[17].color = useColor;
    
    // RIGHT
    cube.verts[18].position = Vec3(0.5f * w, -0.5f * h, 0.5f * d);
    cube.verts[19].position = Vec3(0.5f * w, 0.5f * h, -0.5f * d);
    cube.verts[20].position = Vec3(0.5f * w, -0.5f * h, -0.5f * d);
    
    // set color for this triangle
    useColor = CreateColor(cube.verts[18].position, cube.verts[19].position,
            cube.verts[20].position, color);
    cube.verts[18].color = cube.verts[19].color = cube.verts[20].color = useColor;
    
    cube.verts[21].position = Vec3(0.5f * w, -0.5f * h, 0.5f * d);
    cube.verts[22].position = Vec3(0.5f * w, 0.5f * h, 0.5f * d);
    cube.verts[23].position = Vec3(0.5f * w, 0.5f * h, -0.5f * d);
    
    cube.verts[21].color = cube.verts[22].color = cube.verts[23].color = useColor;
    
    // TOP
    cube.verts[24].position = Vec3(-0.5f * w, 0.5f * h, 0.5f * d);
    cube.verts[25].position = Vec3(0.5f * w, 0.5f * h, -0.5f * d);
    cube.verts[26].position = Vec3(0.5f * w, 0.5f * h, 0.5f * d);
 
    // set color for this triangle
    useColor = CreateColor(cube.verts[24].position, cube.verts[25].position,
            cube.verts[26].position, color);
    cube.verts[24].color = cube.verts[25].color = cube.verts[26].color = useColor;

    
    cube.verts[27].position = Vec3(-0.5f * w, 0.5f * h, 0.5f * d);
    cube.verts[28].position = Vec3(-0.5f * w, 0.5f * h, -0.5f * d);
    cube.verts[29].position = Vec3(0.5f * w, 0.5f * h, -0.5f * d);
    
    cube.verts[27].color = cube.verts[28].color = cube.verts[29].color = useColor;
    
    // BOTTOM
    cube.verts[30].position = Vec3(-0.5f * w, -0.5f * h, -0.5f * d);
    cube.verts[31].position = Vec3(0.5f * w, -0.5f * h, 0.5f * d);
    cube.verts[32].position = Vec3(0.5f * w, -0.5f * h, -0.5f * d);
            
    // set color for this triangle
    useColor = CreateColor(cube.verts[31].position, cube.verts[32].position,
            cube.verts[33].position, color);
    cube.verts[31].color = cube.verts[32].color = cube.verts[33].color = useColor;
    
    cube.verts[33].position = Vec3(-0.5f * w, -0.5f * h, -0.5f * d);
    cube.verts[34].position = Vec3(-0.5f * w, -0.5f * h, 0.5f * d);
    cube.verts[35].position = Vec3(0.5f * w, -0.5f * h, 0.5f * d);
    
    cube.verts[33].color = cube.verts[34].color = cube.verts[35].color = useColor;
    
    // put color and rotate vertices
    wmath::Mat3 rotMat = wmath::Mat3::RotationY(rotation);
    wmath::Mat4 tranMat = wmath::Mat4::Translate(pos);
    for(int i = 0; i < 36; ++i)
    {
        cube.verts[i].position = tranMat * rotMat * (cube.verts[i].position + extr); 
    }
}

Vec3 GetLightColor(int state)
{
    switch(state)
    {
        case TRADEFS::PROCEED:
            return Vec3(0.0f, 0.8f, 0.0f);
        case TRADEFS::STOP:
            return Vec3(0.8f, 0.0f, 0.0f);
        case TRADEFS::OFF:
            return Vec3(0.1f, 0.1f, 0.1f);
        case TRADEFS::STOP_ALMOST:
            return Vec3(0.8f, 0.8f, 0.0f);
        case TRADEFS::PROCEED_BLINKING:
        case TRADEFS::BLINKING:
            return Vec3(0.6f, 0.2f, 0.3f);
        default: 
            return Vec3(0.1f, 0.1f, 0.1f); 
    }
}

void CSimulationView::DrawLights()
{
    std::vector<CTrafficLight>& lights = mModel->GetTrafficLigths();
    std::vector<CTrafficLight>::iterator traIt;
    if( lights.size() > 0)
    {
        std::vector<dCube> traLights;
        dCube lightBounds;
        dCube light;
        Vec3 color;
        Vec3 pos;
        Vec3 posL;
        posL.z -= 0.4f;
        float scale = 1.0f;
        float rot;
        
        for(traIt = lights.begin(); traIt != lights.end(); ++traIt)
        {
            // create cube here
            pos = traIt->GetPosition();
            rot = traIt->GetRotation();
            
            // check scale
            if( traIt->GetPedType() == TRADEFS::PED)
            {
                scale = 0.5f;
            }
            else
                scale = 1.0f;
            
            // base on trafficlight type we create a smaller or bigger version
            addCube(lightBounds, pos, 3.0f * scale, 3.0f * scale, 0.5f, 
                    Vec3(0.1f, 0.1f, 0.1f), rot , Vec3());
            
            // check light state and adjust color to that
            color = GetLightColor( traIt->GetState());
            
            // get position
            addCube(light, pos, 1.5f * scale, 1.5f * scale, 0.25f, 
                    color, rot, posL);
            
            // push the cube
            traLights.push_back(light);
            traLights.push_back(lightBounds);
        }
        
        // put in to vertexbuffer
        traVertexBuffer.SubData(&traLights[0], sizeof(dCube) * traLights.size() );
        
        traShader.Bind();
        int projViewMatrix = glGetUniformLocation(traShader.GetID(), "mvpMatrix");
        
        // draw participants
        wmath::Mat4 projView = mCamera.GetProjection() * mCamera.GetView();
        glUniformMatrix4fv(projViewMatrix, 1, GL_FALSE, (GLfloat*)&projView);

        traVertexBuffer.Bind();
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
        traVertexBuffer.SetAttribPointer(0, 3, GL_FLOAT, sizeof(cubeVert), 0 );
        traVertexBuffer.SetAttribPointer(1, 3, GL_FLOAT, sizeof(cubeVert), (void*)sizeof(Vec3) );

        glDrawArrays(GL_TRIANGLES, 0, traLights.size() * 72);

        traShader.Unbind();
    }
}

void CSimulationView::CreateParticipantCube(dCube& cube, CParticipant& par)
{
    float rot = par.GetRotation();
    Vec3 pos = par.GetPosition();
    Vec3 color = Vec3(0.3f, 0.6f, 0.2f);
    
    switch(par.GetType())
    {
        case TRADEFS::CAR:
                addCube(cube, pos, 6.0f, 5.0f, TRADEFS::CARSIZE, 
                color, rot , Vec3());
            break;
        case TRADEFS::BIKE:
                addCube(cube, pos, 1.0f, 3.0f, TRADEFS::BIKESIZE, 
                color, rot , Vec3());
            break;
        case TRADEFS::PEDESTRIAN:
                addCube(cube, pos, TRADEFS::PEDSIZE, 5.0f, TRADEFS::PEDSIZE, 
                color, rot , Vec3());
            break;
        case TRADEFS::BUS:
                addCube(cube, pos, 8.0f, 14.0f, TRADEFS::BUSSIZE, 
                color, rot , Vec3());
            break;
    }
}

void CSimulationView::DrawParticipants()
{
    std::list<CParticipant>& participants = mModel->GetParticipants();
    std::list<CParticipant>::iterator parIt;
    if( participants.size() > 0)
    {
        std::vector<dCube> parCubes;
        dCube parti;

        for(parIt = participants.begin(); parIt != participants.end(); ++parIt)
        {
            if((*parIt).Hidden())
                continue;
            
            // create the size of the rectangle
            CreateParticipantCube(parti, *parIt);

            parCubes.push_back(parti);
        }
        
        parShader.Bind();
        int projViewMatrix = glGetUniformLocation(parShader.GetID(), "mvpMatrix");

        // put in to vertexbuffer
        parVertexBuffer.SubData(&parCubes[0], sizeof(dCube) * parCubes.size()  );

        // draw participants
        wmath::Mat4 projView = mCamera.GetProjection() * mCamera.GetView();
        glUniformMatrix4fv(projViewMatrix, 1, GL_FALSE, (GLfloat*)&projView);

        parVertexBuffer.Bind();
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
        traVertexBuffer.SetAttribPointer(0, 3, GL_FLOAT, sizeof(cubeVert), 0 );
        traVertexBuffer.SetAttribPointer(1, 3, GL_FLOAT, sizeof(cubeVert), (void*)sizeof(Vec3) );

        glDrawArrays(GL_TRIANGLES, 0, parCubes.size() * 72);

        parShader.Unbind();
    }
}

void CSimulationView::Draw()
{
    // clear the buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // draw scene
    mScene.Draw(&mCamera);

    // draw trafficlights
    DrawLights();

    // draw participants
    DrawParticipants();

    // draw skybox
    mSkybox.Draw();

    // show screen
    glfwSwapBuffers();
}