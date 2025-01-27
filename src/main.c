#include "raylib.h"
#include "resource_dir.h"	// utility header for SearchAndSetResourceDir
#include "stdio.h"
#include "math.h"

typedef struct 
{
	int x,y,z;
	int pitch;
	int yaw;
}Player;

typedef struct
{
	float cos[360];
	float sin[360];
}TrigTables;


void init(Player* p, TrigTables* t)
{
	p->x = 70;
	p->y = -110;
	p->z = 20;
	p->pitch = 0;
	p->yaw = 0;

	for(int i = 0; i < 360; i++)
	{
		t->cos[i] = cos((float)i / 180.0f * PI);
		t->sin[i] = sin((float)i / 180.0f * PI);
	}
}

void movePlayer(Player* p, TrigTables* t)
{
	bool isMPressed = IsKeyDown(KEY_M);
	if(IsKeyDown(KEY_A) && !isMPressed) {p->yaw -= 4; if(p->yaw < 0){p->yaw += 360;}}
	if(IsKeyDown(KEY_D) && !isMPressed) {p->yaw += 4; if(p->yaw > 359){p->yaw -= 360;}}
	int dx = t->sin[p->yaw] * 10.0;
	int dy = t->cos[p->yaw] * 10.0;
	if(IsKeyDown(KEY_W) && !isMPressed) {p->x += dx; p->y += dy;}
	if(IsKeyDown(KEY_S) && !isMPressed) {p->x -= dx; p->y -= dy;}

	if(IsKeyDown(KEY_Q)) {p->x += dy; p->y -= dx;}
	if(IsKeyDown(KEY_E)) {p->x -= dy; p->y += dx;}

	if(IsKeyDown(KEY_A) && isMPressed) {p->pitch -= 1;}
	if(IsKeyDown(KEY_D) && isMPressed) {p->pitch += 1;}
	if(IsKeyDown(KEY_W) && isMPressed) {p->z -= 4;}
	if(IsKeyDown(KEY_S) && isMPressed) {p->z += 4;}
}

void draw3D()
{

}

int main()
{
	Player p;
	TrigTables t;
	init(&p, &t);
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);
	InitWindow(1280, 800, "Hello Raylib");
	SearchAndSetResourceDir("resources");

	//std::cout << &p.x << std::endl;

	while (!WindowShouldClose())
	{
		PollInputEvents();
		BeginDrawing();
		ClearBackground(BLACK);
		
		movePlayer(&p, &t);

		EndDrawing();
	}

	CloseWindow();
	return 0;
}
