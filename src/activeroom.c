#include "activeroom.h"

void ActiveRoom_create(struct ActiveRoom* active, struct Room* room)
{
  unsigned char i,u;
  unsigned char cell;
  //affectation de la salle de base
  active->room = room;
  active->markedForTpTo = -1;
  //TODO: ajouter ici le code relatif aux biomes
  //"mise à zéro" de la salle
  for(i = 0; i != ROOM_MAX_SIDE; i++)
  {
    for(u = 0; u != ROOM_MAX_SIDE; u++)
    {
      active->map[i+u*room->width] = 0x00;
    }
  }
  //initialisation primaire de la salle
  for(i = 0; i != room->width; i++)
  {
    for(u = 0; u != room->height; u++)
    {
      cell = CELL_GROUND;
      if(u == 0 || i == 0 || i == room->width -1 || u == room->height - 1)
      {
        cell = CELL_WALL;
      }
      active->map[i+u*room->width] = cell;
    }
  }
  //ajout des portes
  //correction des duplicatas
  for(i = 0; i != 4; i++)
  {
    if(room->doorTar[i] != -1)
    {
      for(u = 0; u != 4; u++)
      {
        if(i != u && room->doorTar[i] == room->doorTar[u])
        {
          room->doorPos[u] = -1;
          room->doorTar[u] = -1;
        }
      }
    }
  }

  //positionnement de la porte de gauche
  if(room->doorPos[0] != -1)
  {
    active->map[room->doorPos[0]*room->width] = CELL_DOOR + room->doorTar[0];
  }
  //porte du haut
  if(room->doorPos[1] != -1)
  {
    active->map[room->doorPos[1]] = CELL_DOOR + room->doorTar[1];
  }
  //porte de droite
  if(room->doorPos[2] != -1)
  {
    active->map[(room->width-1)+room->doorPos[2]*room->width] = CELL_DOOR + room->doorTar[2];
  }
  //porte du bas
  if(room->doorPos[3] != -1)
  {
    active->map[room->doorPos[3]+(room->height-1)*room->width] = CELL_DOOR + room->doorTar[3];
  }
}

unsigned char ActiveRoom_isCellPassable(struct ActiveRoom* active, const unsigned char x, const unsigned char y)
{
  unsigned int width, height;
  struct Room* room;
  unsigned char r;
  room = active->room;
  width = room->width;
  height = room->height;
  if(x == 0x0F || y == 0x0F || x == width || y == height)
    return false;
  r = active->map[x+y*width] >> 7;
  if(r == 1)
    return false;

  return true;
  //return Entities_interact(x,y);

}

unsigned char ActiveRoom_getCellAt(struct ActiveRoom* active, const unsigned char x, const unsigned char y)
{
  return active->map[x+y*(active->room->width)];
}

unsigned char ActiveRoom_getId(struct ActiveRoom* active)
{
  return active->room->id;
}

void ActiveRoom_getDoorTo(struct ActiveRoom* active, unsigned char room, unsigned char* tab)
{
  unsigned char* done = 0xDE80;
  unsigned char i = 0;
  unsigned char u = 0;
  unsigned char x = 0;
  unsigned char y = 0;
  for(i = 0; i !=active->room->width; i++)
  {
    for(u = 0; u != active->room->height; u++)
    {
      //copie pour corriger un bug étrange
      (*done) = active->map[i+u*active->room->width];
      done++;
      (*done) = CELL_DOOR + room;
      if(active->map[i+u*active->room->width] == CELL_DOOR + room)
      {
        x = i;
        y = u;
      }
    }
  }
  if(x == 0)
    x = x + 1;
  else if(x == active->room->width-1)
    x = x - 1;
  if(y == 0)
      y = y + 1;
  else if(y == active->room->height-1)
      y = y - 1;
  (*tab) = x;
  tab++;
  (*tab) = y;
}

void ActiveRoom_getSize(struct ActiveRoom* active, unsigned char* tab)
{
    (*tab) = active->room->width;
    tab++;
    (*tab) = active->room->height;
}

unsigned char ActiveRoom_getEntitiesType(struct ActiveRoom* active)
{
  unsigned char t;
  t = active->room->entitiesType;
  return t;
}

unsigned char ActiveRoom_getEntityNumber(struct ActiveRoom* active)
{
  unsigned char t;
  t = active->room->entitiesNumber;
  return t;
}
