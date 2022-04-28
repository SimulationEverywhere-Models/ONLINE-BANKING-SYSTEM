/*******************************************************************
*
*  DESCRIPTION: Transaction Process Manager (of Intenet Online 
*               banking System) Atomic Model 
*
*  AUTHOR: Richard Ying Fang
*
*  DATE: 31/10/2007
*
*******************************************************************/

/** include files **/

#include "TransactionProcessManager.h"  
#include "message.h"         // InternalMessage ....
#include "distri.h"          // class Distribution
#include "mainsimu.h"        // class MainSimulator
#include "randlib.h"         // Random numbers library 
#include "strutil.h"         // str2float( ... )
#include <math.h>            // fabs( ... )
#include <stdlib.h>

extern int current_account_balance;
/*******************************************************************
* Function Name: BillPaymentManager
* Description: constructor
********************************************************************/
TransactionProcessManager::TransactionProcessManager( const string &name )
: Atomic( name )
, VBA_IN( addInputPort( "VBA_IN" ) )
, UAB_OUT( addOutputPort( "UAB_OUT" ) )
, LOGOUT( addOutputPort( "LOGOUT" ) )
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
* Description: the TransactionProcessManager receives valid password signal as input, 
* 				as well as invalid bill amount
********************************************************************/
Model &TransactionProcessManager::externalFunction( const ExternalMessage &msg )
{
  if ( this->state() == passive)
   {

    if (msg.port() == VBA_IN )  
     {
        holdIn( active, Time( static_cast<float>( fabs( distribution().get() ) ) ) ) ;            	
        
        billAmount = msg.value();
        
        current_account_balance = current_account_balance - billAmount;
    	
     }
    
   }
	return *this ;
}

/*******************************************************************
* Function Name: internalFunction
********************************************************************/
Model &TransactionProcessManager::internalFunction( const InternalMessage & )
{
	passivate();
	return *this;
}

/*******************************************************************
* Function Name: outputFunction
********************************************************************/
Model &TransactionProcessManager::outputFunction( const InternalMessage &msg )
{

	
	  
    sendOutput( msg.time(), UAB_OUT, current_account_balance );
    sendOutput( msg.time(), LOGOUT, 1 );
         
	return *this;
}

TransactionProcessManager::~TransactionProcessManager()
{
	delete dist;
}
