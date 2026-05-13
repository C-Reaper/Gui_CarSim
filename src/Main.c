#include "/home/codeleaded/System/Static/Library/WindowEngine1.0.h"
#include "/home/codeleaded/System/Static/Library/TDWorld.h"


TDWorld world;

void Setup(AlxWindow* w){
    ResizeAlxFont(10,10);

    if(Files_isFile("./data/World0.tdworld")){
        world = TDWorld_Load("./data/World0.tdworld",Sprite_Load("/home/codeleaded/Graphics/CarGame/City_Roads.png"));
    }else{
        world = TDWorld_New(100,100,Sprite_Load("/home/codeleaded/Graphics/CarGame/City_Roads.png"));
    }
    // (TDEngine*)TDEngine_Gasoline_New(6,100.0f,60.0f)
    // (TDEngine*)TDEngine_Diesel_New(6,100.0f,60.0f)
    // (TDEngine*)TDEngine_Electric_New(100.0f,10.0f)
    TDWorld_LoadCar(&world,0.0f,0.0f,"./assets/Car_Green_Fast.png",AlxFont_MAKE_HIGH(16,32),(TDEngine*)TDEngine_Gasoline_New(6,100.0f,60.0f));
}
void Update(AlxWindow* w){
    if(Stroke(ALX_MOUSE_L).PRESSED){
        const Vec2 m_world = { world.car.pos.x,-world.car.pos.y };
        
        if(m_world.x >= 0 && m_world.x < (int)world.width && m_world.y >= 0 && m_world.y < (int)world.height){
            const unsigned int tx = (unsigned int)m_world.x;
            const unsigned int ty = (unsigned int)m_world.y;
            const unsigned int index = ty * world.width + tx;
            
            if(world.world[index] < 255U)
                world.world[index]++;
        }
    }else if(Stroke(ALX_MOUSE_R).PRESSED){
        const Vec2 m_world = { world.car.pos.x,-world.car.pos.y };
        
        if(m_world.x >= 0 && m_world.x < (int)world.width && m_world.y >= 0 && m_world.y < (int)world.height){
            const unsigned int tx = (unsigned int)m_world.x;
            const unsigned int ty = (unsigned int)m_world.y;
            const unsigned int index = ty * world.width + tx;
            
            if(world.world[index] > 0U)
                world.world[index]--;
        }
    }else if(Stroke(ALX_MOUSE_M).PRESSED){
        const Vec2 m_world = { world.car.pos.x,-world.car.pos.y };
        
        if(m_world.x >= 0 && m_world.x < (int)world.width && m_world.y >= 0 && m_world.y < (int)world.height){
            const unsigned int tx = (unsigned int)m_world.x;
            const unsigned int ty = (unsigned int)m_world.y;
            const unsigned int index = ty * world.width + tx;
            
            world.world[index] = 0U;
        }
    }

    if(Stroke(ALX_KEY_W).DOWN)          TDCar_Interact(&world.car,TDENGINE_GASOLINE_INTERACT_GASDOWN,(float[]){ 1.0f });
    else                                TDCar_Interact(&world.car,TDENGINE_GASOLINE_INTERACT_GASUP,NULL);
    
    if(Stroke(ALX_KEY_S).DOWN)          TDCar_Break(&world.car,0.98f);
    if(Stroke(ALX_KEY_A).DOWN)          TDCar_Turn(&world.car, F32_PI * w->ElapsedTime);
    if(Stroke(ALX_KEY_D).DOWN)          TDCar_Turn(&world.car,-F32_PI * w->ElapsedTime);
    
    if(Stroke(ALX_KEY_ENTER).DOWN)      TDCar_Start(&world.car);

    if(Stroke(ALX_KEY_R).PRESSED)       TDCar_Interact(&world.car,TDENGINE_GASOLINE_INTERACT_GEARUP,NULL);
    if(Stroke(ALX_KEY_F).PRESSED)       TDCar_Interact(&world.car,TDENGINE_GASOLINE_INTERACT_GEARDOWN,NULL);
    
    if(Stroke(ALX_KEY_UP).DOWN)      world.zoom *= 1.01f;
    if(Stroke(ALX_KEY_DOWN).DOWN)    world.zoom *= 0.99f;
    
    TDCar_Update(&world.car,w->ElapsedTime);
    
    Clear(BLUE);

    TDWorld_Render(WINDOW_STD_ARGS,&world);

    TDCar_RenderSpeed(WINDOW_STD_ARGS,&world.car,200.0f,GetHeight() - 200.0f,200.0f);
    TDCar_RenderWTN(WINDOW_STD_ARGS,&world.car,600.0f,GetHeight() - 200.0f,200.0f);
    TDCar_RenderEngine(WINDOW_STD_ARGS,&world.car,800.0f,GetHeight() - 400.0f,400.0f);
}
void Delete(AlxWindow* w){
    TDWorld_Save(&world,"./data/World0.tdworld");
    TDWorld_Free(&world);
}

int main(){
    if(Create("Car Simulation",1900,1000,1,1,Setup,Update,Delete))
        Start();
    return 0;
}
