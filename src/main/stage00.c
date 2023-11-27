/*
   stage00.c 

   Copyright (C) 1997-1999, NINTENDO Co,Ltd.
*/

#include <assert.h>
#include <nusys.h>
#include "main.h"
#include "graphic.h"

static f32 lodPos_x = 400.0; /* Display position X */

static f32 lodRot_x; /* Rotating angle for X axis */
static f32 lodRot_y; /* Rotating angle for Y axis */
static f32 lodRot_z; /* Rotating angle for Z axis */

static float cameraPos = 0; /* The display camera position */

float cameraFov = 120.0f;

void shadetri(Dynamic* dynamicp);

// Initialize the projection matrix
  u16 persp_norm;

  static LookAt lookat;

/* Make the display list and activate the task. */

/* Initialize stage 0 */
void initStage00(void)
{
    /* Initialize parameters */
    char conbuf[20]; //text buffer?

    Mtx rotate_x;
  Mtx rotate_y; 
  Mtx rotate_z; 

  //lodPos_x = (f32)100.0;

  lodRot_x = 0.0;
    lodRot_y = 0.0;
    lodRot_z = 0.0;
}

void makeDL00(void)
{
  /* Specify the display list buffer  */
  glistp = gfx_glist;

  /*  The initialization of RCP  */
  gfxRCPInit();

  /* Clear the frame buffer and the Z-buffer  */
  gfxClearCfb();

  /* The set of projection modeling matrices  */
  /* guFrustum(&gfx_dynamic.projection,
	  -(float)SCREEN_WD/2.0F, (float)SCREEN_WD/2.0F,
	  -(float)SCREEN_HT/2.0F, (float)SCREEN_HT/2.0F,
	  1.0F, 10.0F, 1.0F); */ //guFrustum is for prospective projection
  //guRotate(&gfx_dynamic.modeling, 0.0F, 0.0F, 0.0F, 1.0F);

  

  guPerspective(
    &gfx_dynamic.projection,
    &persp_norm,
    cameraFov,
    (float)SCREEN_WD / (float)SCREEN_HT,
    10,
    10000,
    1.0
  );

  guLookAtReflect(&gfx_dynamic.viewing, &lookat,
		  0, 0, 600,
		  0, 0, 0,
		  0, 1, 0);

  guRotate(&gfx_dynamic.modeling, lodRot_x, 0.0F, 1.0F, 0.0f);

  guTranslate(&gfx_dynamic.translate, 0, 0, lodPos_x); //not working?

  

  /* guRotate(&rotate_x, lodRot_x, 1.0F, 0.0F, 0.0F);
  guRotate(&rotate_y, lodRot_y, 0.0F, 1.0F, 0.0F);
  guRotate(&rotate_z, lodRot_z, 0.0F, 0.0F, 1.0F); */

  //guRotate(&gfx_dynamic.modeling, 1.0F, lodRot_x, lodRot_y, lodRot_z);

  /* Draw a square  */
  shadetri(&gfx_dynamic);

  

  /* End the construction of the display list  */
  gDPFullSync(glistp++);
  gSPEndDisplayList(glistp++);

  /* Check if all are put in the array  */
  assert(glistp - gfx_glist < GFX_GLIST_LEN);

  /* Activate the RSP task.  Switch display buffers at the end of the task. */
  nuGfxTaskStart(gfx_glist,
		 (s32)(glistp - gfx_glist) * sizeof (Gfx),
		 NU_GFX_UCODE_F3DEX , NU_SC_SWAPBUFFER);

    //check if controller is connected
     //if(!(contPattern & 0x1))
     /* if(contPattern & 0x1)
     {
        nuDebConTextPos(0,64,64);
        //nuDebConTextPos(0,12,23);
        //sprintf(conbuf,"cameraPos=s",cameraPos);
        sprintf(conbuf,"cameraPos=%5.1f",cameraPos);
        nuDebConCPuts(0, conbuf);
     } */
     //osSyncPrintf("A button Push\n");
}

/* The game progressing process for stage 0 */
void updateGame00(void)
{  

  lodRot_x += (f32)1.0;

  lodPos_x += (f32)1.0;

  if(lodPos_x > 500.0) lodPos_x = 300.0;

  //guRotate(&gfx_dynamic.modeling, 45.0F, 0.0F, 0.0F, 1.0F);
  //osSyncPrintf("B button Push\n");
  /* Read data of the controller 1 */
  //nuContDataGetEx(contdata,0);

  /* Adjust play of stick */
  /* if( contdata[0].stick_x > -5 && contdata[0].stick_x < 5 )
      contdata[0].stick_x = 0;
  if( contdata[0].stick_y > -5 && contdata[0].stick_y < 5 )
      contdata[0].stick_y = 0; */

  /* 3D stick changes the rotating speed */
  /* lodRot_x += (f32)contdata[0].stick_y/10.0;
  lodRot_y += (f32)contdata[0].stick_x/10.0; */

  /* Adjust angle range */
  /* if(lodRot_x<0.0)
      lodRot_x+=360.0;
  else if(lodRot_x>360.0)
      lodRot_x-=360.0;
  if(lodRot_y<0.0)
      lodRot_y+=360.0;
  else if(lodRot_y>360.0)
      lodRot_y-=360.0;
  if(lodRot_z<0.0)
      lodRot_z+=360.0;
  else if(lodRot_z>360.0)
      lodRot_z-=360.0; */


  //guRotate(&gfx_dynamic.modeling, 1.0F, 0.0F, 0.0F, 0.0F);
  //static float vel = 1.0;

  /* Data reading of controller 1 */
  //nuContDataGetEx(contdata,0);

  if(contdata[0].trigger & A_BUTTON)
    {
      //vel = -vel;
      lodPos_x += 64.0;
      osSyncPrintf("A button Push\n");
    }

    osSyncPrintf("A button Push\n");

  /* Change the display position by stick data */
  //cameraPos = contdata->stick_x;
  //triPos_y = contdata->stick_y;

  /* The reverse rotation by the A button */
  /* if(contdata[0].trigger & A_BUTTON)
    {
      vel = -vel;
      osSyncPrintf("A button Push\n");
    } */

  /* Rotate fast while pushing the B button */
  /* if(contdata[0].button & B_BUTTON)
    theta += vel * 3.0;
  else
    theta += vel;

  if(theta>360.0)
      theta-=360.0;
  else if (theta<0.0)
      theta+=360.0; */

}


/* The vertex coordinate  */
static Vtx shade_vtx[] =  {
        /* {        -64,  64, -1, 0, 0, 0, 0, 0xff, 0, 0xff	},
        {         64,  64, -1, 0, 0, 0, 0, 0, 0, 0xff	},
        {         64, -64, -1, 0, 0, 0, 0, 0, 0xff, 0xff	},
        {        -64, -64, -1, 0, 0, 0, 0xff, 0, 0, 0xff	}, */

        /* {        -64,  -64, -64, 0, 0, 0, 0, 0xff, 0, 0xff	},
        {         64,  -64, -64, 0, 0, 0, 0, 0, 0, 0xff	},
        {         64, -64, 64, 0, 0, 0, 0, 0, 0xff, 0xff	},
        {        -64, -64, 64, 0, 0, 0, 0xff, 0, 0, 0xff	},

        {        -64,  64, 64, 0, 0, 0, 0, 0xff, 0, 0xff	},
        {         -64,  64, -64, 0, 0, 0, 0, 0, 0, 0xff	},
        {         64, 64, -64, 0, 0, 0, 0, 0, 0xff, 0xff	},
        {        64, 64, 64, 0, 0, 0, 0xff, 0, 0, 0xff	}, */

        {        -64,  -64, -64, 0, 0, 0, 0, 0, 0xff, 0xff	},
        {         64,  -64, -64, 0, 0, 0, 0, 0, 0xff, 0xff	},
        {         64, -64, 64, 0, 0, 0, 0, 0, 0xff, 0xff	},
        {        -64, -64, 64, 0, 0, 0, 0, 0, 0xff, 0xff	},

        {        -64,  64, 64, 0, 0, 0, 0, 0, 0xff, 0xff	},
        {         -64,  64, -64, 0, 0, 0, 0, 0, 0xff, 0xff	},
        {         64, 64, -64, 0, 0, 0, 0, 0, 0xff, 0xff	},
        {        64, 64, 64, 0, 0, 0, 0, 0, 0xff, 0xff	},
};

/* Draw a square  */
void shadetri(Dynamic* dynamicp)
{
  gSPPerspNormalize(glistp++, persp_norm);

  gSPLookAt(glistp++, &lookat);

  gSPMatrix(glistp++,OS_K0_TO_PHYSICAL(&(dynamicp->projection)),
		G_MTX_PROJECTION|G_MTX_LOAD|G_MTX_NOPUSH);

    gSPMatrix(glistp++, OS_K0_TO_PHYSICAL(&(dynamicp->viewing)),
	    G_MTX_PROJECTION|G_MTX_MUL|G_MTX_NOPUSH);

    gSPMatrix(glistp++, OS_K0_TO_PHYSICAL(&(dynamicp->translate)),
	    G_MTX_MODELVIEW|G_MTX_LOAD|G_MTX_NOPUSH);
    
  gSPMatrix(glistp++,OS_K0_TO_PHYSICAL(&(dynamicp->modeling)),
		G_MTX_MODELVIEW|G_MTX_MUL|G_MTX_NOPUSH);

  
    
  //gSPVertex(glistp++,&(shade_vtx[0]),4, 0);
  gSPVertex(glistp++,&(shade_vtx[0]),8, 0);

  gDPPipeSync(glistp++);
  gDPSetCycleType(glistp++,G_CYC_1CYCLE);
  gDPSetRenderMode(glistp++,G_RM_AA_OPA_SURF, G_RM_AA_OPA_SURF2);
  gDPSetDepthSource(glistp++, G_ZS_PRIM);
  gDPSetPrimDepth(glistp++, 0, 0);
  gSPClearGeometryMode(glistp++,0xFFFFFFFF);
  gSPSetGeometryMode(glistp++,G_SHADE| G_SHADING_SMOOTH);

  //gSP2Triangles(glistp++,0,1,2,0,0,2,3,0);

  //front
  gSP2Triangles(glistp++,4,7,2,4,4,2,3,4);
  //top
  gSP2Triangles(glistp++,5,6,7,5,5,7,4,5);
  //left
  gSP2Triangles(glistp++,5,4,3,5,5,3,0,5);
  //back
  gSP2Triangles(glistp++,6,5,0,6,6,0,1,6);
  //bottom
  gSP2Triangles(glistp++,3,2,1,3,3,1,0,3);
  //right
  gSP2Triangles(glistp++,7,6,1,7,7,1,2,7);
}
