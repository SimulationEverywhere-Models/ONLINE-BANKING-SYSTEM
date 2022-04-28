/*******************************************************************
*
*  DESCRIPTION: Bill Payment Manager (of Intenet Online 
*               banking System) Atomic Model 
*
*  AUTHOR: Richard Ying Fang
*
*  DATE: 31/10/2007
*
*******************************************************************/

/** include files **/

#include "BillPaymentManager.h"  
#include "message.h"         // InternalMessage ....
#include "distri.h"          // class Distribution
#include "mainsimu.h"        // class MainSimulator
#include "randlib.h"         // Random numbers library 
#include "strutil.h"         // str2float( ... )
#include <math.h>            // fabs( ... )
#include <stdlib.h>

//global variable 

int current_account_balance = 3000;

/*******************************************************************
* Function Name: BillPaymentManager
* Description: constructor
********************************************************************/
BillPaymentManager::BillPaymentManager( const string &name )
: Atomic( name )
, VPN_IN( addInputPort( "VPN_IN" ) )
, IBA_IN( addInputPort( "IBA_IN" ) )
, VBA_OUT( addOutputPort( "VBA_OUT" ) )
, IBA_OUT( addOutputPort( "IBA_OUT" ) )
{
	try
	{
		dist = Distribution::create( MainSimulator::Instance().getParameter( description(), "distribution" ) );

		MASSERT( dist );

		for ( register int i = 0 ; i < dist->varCount() ; i++ )
		{
			string parameter( MainSimulator::Instance().getParameter( description(), dist->getVar(i) ) ) ;
			dist->setVar( i, str2float( parameter ) ) ;
		}
	} catch( InvalidDistribution &e )
	{
		e.addText( "The model " + description() + " has distribution problems!" ) ;
		e.print(cerr);
		MTHROW( e ) ;
	} catch( MException &e )
	{
		MTHROW( e ) ;
	}
}

/*******************************************************************
* Function Name: externalFunction
* Description: the BillPaymentManager receives valid password signal as input, 
* 				as well as invalid bill amount
********************************************************************/
Model &BillPaymentManager::externalFunction( const ExternalMessage &msg )
{
	if ( this->state() == passive)
   {

    if ( (msg.port() == VPN_IN ) && (msg.port() != IBA_IN  )  ) 
     {
        holdIn( active, Time( static_cast<float>( fabs( distribution().get() ) ) ) ) ;            	
        
        // get a random number of 1 to 4000
    	randBilAmount =  rand()%4000 +1 ;
     }
    if (msg.port() == IBA_IN )   
     {
       holdIn( active, Time( static_cast<float>( fabs( distribution().get() ) ) ) ) ;
        // get a random number of 1 to 4000
    	randBilAmount =  rand()%4000 +1 ;
     }
   }
	return *this ;
	
	
  
}

/*******************************************************************
* Function Name: internalFunction
********************************************************************/
Model &BillPaymentManager::internalFunction( const InternalMessage & )
{
	passivate();
	return *this;
}

/*******************************************************************
* Function Name: outputFunction
********************************************************************/
Model &BillPaymentManager::outputFunction( const InternalMessage &msg )
{
	      if ( randBilAmount <= current_account_balance )
         sendOutput( msg.time(), VBA_OUT, randBilAmount );
      else
        {
         sendOutput( msg.time(), IBA_OUT, 1 );
         }
	return *this;
}

BillPaymentManager::~BillPaymentManager()
{
	delete dist;
}
