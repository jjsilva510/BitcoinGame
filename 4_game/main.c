#include <gb/gb.h>
#include <stdio.h>
#include "GameCharacter.c"
#include "GameSprites.c"


struct GameCharacter ship;
struct GameCharacter bug; 
struct GameCharacter bullet; //TS

UBYTE spritesize = 8;

void performantdelay(UINT8 numloops)
{
    UINT8 i;
    for(i = 0; i < numloops; i++)
    {
        wait_vbl_done();
    }
}

void movegamecharacter(struct GameCharacter* character, UINT8 x, UINT8 y)
{
    move_sprite(character->spritids[0], x, y);
    move_sprite(character->spritids[1], x + spritesize, y);
    move_sprite(character->spritids[2], x, y + spritesize);
    move_sprite(character->spritids[3], x + spritesize, y + spritesize);
}

void setupship()
{
    ship.x = 80;
    ship.y = 130;
    ship.width = 16;
    ship.height = 16;
    //above is the location and size of ship sprite.

    // load sprites for ship
    set_sprite_tile(0, 0);
    ship.spritids[0] = 0;
    set_sprite_tile(1, 1);
    ship.spritids[1] = 1;
    set_sprite_tile(2, 2);
    ship.spritids[2] = 2;
    set_sprite_tile(3, 3);
    ship.spritids[3] = 3;

    movegamecharacter(&ship, ship.x, ship.y);
}

void setupbug()
{
    bug.x = 80;
    bug.y = 30;
    bug.width = 16;
    bug.height = 16;
    //above is the location and size of bug sprite.

    // load sprites for bug
    set_sprite_tile(4, 4);
    bug.spritids[0] = 4;
    set_sprite_tile(5, 5);
    bug.spritids[1] = 5;
    set_sprite_tile(6, 6);
    bug.spritids[2] = 6;
    set_sprite_tile(7, 7);
    bug.spritids[3] = 7;

    movegamecharacter(&bug, bug.x, bug.y);
}

void setupbullet() // TS *whole method
{
    bullet.x = 80;
    bullet.y = 130;
    bullet.width = 16;
    bullet.height = 16;

    set_sprite_tile(8, 8);
    bullet.spritids[0] = 8;
    set_sprite_tile(9, 9);
    bullet.spritids[1] = 9;
    set_sprite_tile(10, 10);
    bullet.spritids[2] = 10;
    set_sprite_tile(11, 11);
    bullet.spritids[3] = 11;

    movegamecharacter(&bullet, bullet.x, bullet.y);
}

void main()
{
    set_sprite_data(0, 12, GameSprites);
    setupship();
    setupbug();
    setupbullet();

    SHOW_SPRITES;
    DISPLAY_ON;

    while(1)
    {
        if (joypad() & J_LEFT)
        {
            ship.x -= 2;
            movegamecharacter(&ship, ship.x, ship.y);
        }
        if (joypad() & J_RIGHT)
        {
            ship.x += 2;
            movegamecharacter(&ship, ship.x, ship.y);
        }

        bug.y += 5;
        // Moves bug sprite down from top of screen

        if (bug.y >= 144)
        {
            bug.y = 0;
            bug.x = ship.x;
        }

        movegamecharacter(&bug, bug.x, bug.y)

        if (joypad() & J_A) 
        // (9/29) Finally works, but needs fixing.
        {
            //bullet.y -= 5;
            bullet.y = ship.y - 8;
            while (bullet.y >= 30)
            {
                bullet.y -= 5;
                //if (bullet.y <= 0)
                //{
                //    bullet.y = 255;                    
                //}
                movegamecharacter(&bullet, bullet.x, bullet.y);
                performantdelay(5);
            }
            bullet.y = 0;
            movegamecharacter(&bullet, bullet.x, bullet.y);
        }
        performantdelay(5);
    }
}