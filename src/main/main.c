/*
   main.c

   NuSYSTEM sample nu0

   Copyright (C) 1997-1999, NINTENDO Co,Ltd.	
   */

#include <nusys.h>
#include <stdbool.h> 
#include "main.h"

bool testy = false;

/* Declaration of the prototype  */
void stage00(int);

/* Declaration of the external function  */
void initStage00(void);
void makeDL00(void);
void updateGame00(void);


/* The global variable  */
NUContData	contdata[1]; /* Read data of 1 controller  */
u8 contPattern;		     /* The pattern connected to the controller  */

/*------------------------
	Main
--------------------------*/
void mainproc(void)
{
  /* The initialization of graphic  */
  nuGfxInit();

  /* The initialization of the controller manager  */
  contPattern = nuContInit();

  /* Initialize for stage00() */
  initStage00();

  /* Register call-back  */
  nuGfxFuncSet((NUGfxFunc)stage00);
  /* The screen display ON */
  nuGfxDisplayOn();

  while(1)
    ;
}

/*-----------------------------------------------------------------------------
  The call-back function 

  pendingGfx which is passed from Nusystem as the argument of the call-back 
  function is the total number of RCP tasks that are currently processing 
  and waiting for the process. 
-----------------------------------------------------------------------------*/

void stage00(int pendingGfx)
{
  /* Perform display processing if there are no RCP tasks being processed. */
  if(pendingGfx < 1)
    makeDL00();	

    /* if(testy == false)
    {
      makeDL00();	
      testy = true;
    } */
    	

  /* Game status process */
  updateGame00(); 
}

