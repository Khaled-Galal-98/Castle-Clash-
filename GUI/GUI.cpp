#include "GUI.h"

//////////////////////////////////////////////////////////////////////////////////////////
GUI::GUI()
{
	pWind = new window(WindWidth+15,WindHeight,0,0);
	pWind->ChangeTitle("The Castle Game");

	DrawMenu();

	ClearStatusBar();
	ClearBattleArea();
	pWind->SetPen(BLACK);
	pWind->SetBrush(BLACK);
	pWind->DrawRectangle(241,53,601,274);
	pWind->DrawRectangle(960,53,601,274);
	pWind->DrawRectangle(960,500,601,274);
	pWind->DrawRectangle(241,500,601,274);
	DrawCastle();
	IntialTextheight = 150;
	IntialTextWidth = 150;
	
	
}
//////////////////////////////////////////////////////////////////////////////////////////
GUI::~GUI()
{
	delete pWind;
}

//////////////////////////////////////////////////////////////////////////////////////////
// ================================== INPUT FUNCTIONS ====================================
//////////////////////////////////////////////////////////////////////////////////////////

void GUI::GetPointClicked(Point &P) const
{
	pWind->WaitMouseClick(P.x, P.y);	//Wait for mouse click
}
//////////////////////////////////////////////////////////////////////////////////////////
void GUI::ResetTextWidth() 
{
	IntialTextWidth = 0;
}
//////////////////////////////////////////////////////////////////////////////////////////
void GUI::ResetTextHeight() 
{
	IntialTextheight = 150;
}
///////////////////////////////////////////////////////////////////////////////////////////
void GUI::IntializingWidth() 
{
	IntialTextWidth = 150;
}
///////////////////////////////////////////////////////////////////////////////////////////
void GUI::ExtendWidth() 
{
	IntialTextWidth = 600;
}
///////////////////////////////////////////////////////////////////////////////////////////

void GUI::DecrementTextHeight(int i)
{
	IntialTextheight = 150;
	IntialTextheight -= (15*i);
}
//////////////////////////////////////////////////////////////////////////////////////////
string GUI::GetString() const 
{
	string Label;
	char Key;
	while(1)
	{
		pWind->WaitKeyPress(Key);
		if(Key == 27 )	//ESCAPE key is pressed
			return "";	//returns nothing as user has cancelled label
		if(Key == 13 )	//ENTER key is pressed
			return Label;
		if((Key == 8) && (Label.size() >= 1))	//BackSpace is pressed
			Label.resize(Label.size() -1 );			
		else
			Label += Key;
		
		PrintMessage(Label);
	}
}

//////////////////////////////////////////////////////////////////////////////////////////
// ================================== OUTPUT FUNCTIONS ===================================
//////////////////////////////////////////////////////////////////////////////////////////

void GUI::PrintMessage(string msg) const	//Prints a message on status bar
{
	//ClearStatusBar();	//First clear the status bar
	
	pWind->SetPen(BLUE);
	pWind->SetFont(15, BOLD , BY_NAME, "Comic Sans MS");   
	pWind->DrawString(IntialTextWidth, WindHeight - (int) (IntialTextheight), msg); // You may need to change these coordinates later 
	                                                                      // to be able to write multi-line
	
}
//////////////////////////////////////////////////////////////////////////////////////////
void GUI::DrawString(const int iX, const int iY, const string Text)
{
	pWind->SetPen(DARKRED);
	pWind->SetFont(18, BOLD , BY_NAME, "Arial");   
	pWind->DrawString(iX, iY, Text);
}
//////////////////////////////////////////////////////////////////////////////////////////
void GUI::DrawMenu() const
{
	//You can draw the menu icons any way you want.
	//Below is one possible way

	//First prepare List of images for each menu item
	//To control the order of these images in the menu, 
	//reoder them in enum MenuItem
	string MenuItemImages[MENU_ITM_COUNT];

	MenuItemImages[MENU_I_MODE] = "images\\MenuItems\\MENU_I_MODE.jpg";
	MenuItemImages[MENU_SBS_MODE] = "images\\MenuItems\\MENU_SBS_MODE.jpg";
	MenuItemImages[MENU_S_MODE] = "images\\MenuItems\\MENU_S_MODE.jpg";


	// You should add an icon for each mode of operation (silent, step by step, ...etc.)

	//Draw menu item one image at a time
	for(int i=0; i<MENU_ITM_COUNT; i++)
		pWind->DrawImage(MenuItemImages[i], i*MenuItemWidth, 0, MenuItemWidth, MenuBarHeight);

	//Draw a line under the menu bar
	pWind->SetPen(BROWN, 3);
	pWind->DrawLine(0, MenuBarHeight, WindWidth, MenuBarHeight);	

}
//////////////////////////////////////////////////////////////////////////////////////////
void GUI::ClearStatusBar() const
{
	pWind->SetPen(WHITE, 3);
	pWind->SetBrush(WHITE);
	pWind->DrawRectangle(0, WindHeight - StatusBarHeight , WindWidth, WindHeight);	

	pWind->SetPen(BROWN, 3);
	pWind->DrawLine(0, WindHeight - StatusBarHeight , WindWidth, WindHeight - StatusBarHeight);	
}
///////////////////////////////////////////////////////////////////////////////////
void GUI::ClearBattleArea() const
{
	// Clearing the battle area
	pWind->SetPen(WHITE, 3);
	pWind->SetBrush(WHITE);
	pWind->DrawRectangle(0, MenuBarHeight, WindWidth, WindHeight - StatusBarHeight);
}
///////////////////////////////////////////////////////////////////////////////////
void GUI::DrawCastle() const
{
	int L = CastleWidth / 2;

	string MenuCastle = "images\\MenuItems\\Menu_Castle.jpg";
	string MenuTower = "images\\MenuItems\\MENU_TOWER.jpg";


	// 1- Drawing the brown square of the castle
	pWind->SetPen(BROWN);
	pWind->SetBrush(BROWN);
	//Drawing a pic for the main castle
	pWind->DrawImage(MenuCastle, (480+60), (155+60), 120, 120);
	// 2- Drawing the 2 brown crossed lines (for making 4 regions)
	pWind->SetPen(BROWN, 3);
	pWind->DrawLine(0, YHalfBattleArea, WindWidth, YHalfBattleArea);
	pWind->DrawLine(WindWidth/2, MenuBarHeight, WindWidth/2, WindHeight-StatusBarHeight);

	// 3- Drawing the 2 white crossed lines (inside the castle)
	pWind->SetPen(WHITE);
	pWind->DrawLine(WindWidth/2, YHalfBattleArea - CastleWidth/2, WindWidth/2, YHalfBattleArea + CastleWidth/2);
	pWind->DrawLine(WindWidth/2 - CastleWidth/2, YHalfBattleArea, WindWidth/2 + CastleWidth/2, YHalfBattleArea);

	// 4- Drawing the 4 white squares inside the castle (one for each tower)
	pWind->SetPen(WHITE);
	pWind->SetBrush(WHITE);
	//Drawing 4 pics to represent the towers
	pWind->DrawImage(MenuTower, CastleStartX, CastleStartY, 80, 80);
	pWind->DrawImage(MenuTower, CastleStartX ,CastleEndY - 80, 80, 80);
	pWind->DrawImage(MenuTower, CastleEndX -80 ,CastleStartY , 80, 80);
	pWind->DrawImage(MenuTower, CastleEndX -80 ,CastleEndY -80, 80, 80);

	// 6- Drawing the 2 vertical brown lines at distance 60
	// that is because some rounding errors may occur if you choose another width and height for the window
	// so we draw 2 vertical lines at distance 60 to mark it
	pWind->SetPen(BROWN);
	pWind->DrawLine(CastleStartX - MaxDistance*EnemyWidth - MaxDistance -1, MenuBarHeight,
		CastleStartX - MaxDistance*EnemyWidth - MaxDistance -1, WindHeight-StatusBarHeight);
	pWind->DrawLine(CastleEndX + MaxDistance*EnemyWidth + MaxDistance +1, MenuBarHeight,
		CastleEndX + MaxDistance*EnemyWidth + MaxDistance +1, WindHeight-StatusBarHeight);
}
//////////////////////////////////////////////////////////////////////////////////////////
void GUI::DrawEnemy(const Enemy & E, int YPos) const       // It's a private function
{
	color clr = E.GetColor();
	REGION Region = E.GetRegion();
	int Distance = E.GetDistance();
	int Type = E.GetType();

	int x, y, refX, refY;
	//First calculate x,y position of the enemy on the output screen
	//It depends on the region and the enemy distance
	switch (Region)
	{
	case A_REG:
		refX = (WindWidth/2 - CastleWidth/2);
		refY = YHalfBattleArea- 1 - EnemyWidth; //
		x = refX - Distance*EnemyWidth - Distance; //(Distance)
		y = refY - YPos*EnemyHeight - YPos; // YPos
		break;
	case B_REG:
		refX = (WindWidth/2 + CastleWidth/2);
		refY = YHalfBattleArea- 1 - EnemyWidth; //
		x = refX + (Distance-1)*EnemyWidth + Distance; //(Distance)
		y = refY - YPos*EnemyHeight - YPos; // YPos
		break;
	case C_REG:
		refX = (WindWidth/2 + CastleWidth/2);
		refY = YHalfBattleArea + 2 + EnemyWidth; //
		x = refX + (Distance-1)*EnemyWidth + Distance; //(Distance)
		y = refY + (YPos-1)*EnemyHeight + YPos; // YPos
		break;
	case D_REG:
		refX = (WindWidth/2 - CastleWidth/2);
		refY = YHalfBattleArea + 2 + EnemyWidth; //
		x = refX - Distance*EnemyWidth - Distance; //(Distance)
		y = refY + (YPos-1)*EnemyHeight + YPos; // YPos
		break;
	default:
		break;
	}

	// Drawing the enemy
	pWind->SetPen(clr);
	pWind->SetBrush(clr);
	pWind->DrawRectangle(x, y, x + EnemyWidth, y + EnemyHeight);
}
//////////////////////////////////////////////////////////////////////////////////////////
/* A function to draw a list of enemies and ensure there is no overflow in the drawing*/
// To use this function, you must prepare its input parameters as specified
// [Input Parameters]:
//    enemies [ ] : array of enemy pointers (ALL enemies from all regions in one array)
//    size : the size of the array (total no. of enemies)
void GUI::DrawEnemies(Enemy* enemies[], int size) const
{
	//draw enemies at each region 
	for(int region = A_REG; region <= D_REG; region++)
	{
		int CountEnemies = 0;	// count Enemies at the same distance to draw them vertically if they are <= 15 enemy 
		                        // else print number of enemy in the region
		bool draw=true;
		for(int distance = MaxDistance ; distance >= MinDistance ; distance--)
		{
			CountEnemies = 0;

			for(int i = 0 ; i < size ; i++)
			{	
				if(enemies[i]->GetDistance() == distance && enemies[i]->GetRegion() == region)
				{
					CountEnemies++;
				}
			}
			if(CountEnemies > 15)
			{
				draw=false;
				break;
			}
		}
		if(draw)
		{
			for( int distance = MaxDistance ; distance > 1 ; distance-- )
			{
				CountEnemies=0;

				for(int i = 0 ; i < size ; i++)
				{	
					if(enemies[i]->GetDistance() == distance && enemies[i]->GetRegion() == region)
					{
						DrawEnemy(*(enemies[i]), CountEnemies + 1);
						CountEnemies++;
					}
				}
			}
		}
		else // print message maximum reached in this region
		{
			PrintMessage("Cannot Draw Enemies of region " + to_string(region+1) + 
				"! More than" + to_string(MaxVerticaEnemies) + " enemies are in the same region and distance..");
			Sleep(1000); // because may be more than one region has drawing overflow
		}
	}
}


void GUI::DrawUnpaved(int x1,int x2,int x3,int x4)
{
	pWind->SetPen(BLACK);
	pWind->SetBrush(BLACK);

	pWind->DrawRectangle(x1,53,601,274);
	pWind->DrawRectangle(x2,53,601,274);
	pWind->DrawRectangle(x3,500,601,274);
	pWind->DrawRectangle(x4,500,601,274);
}