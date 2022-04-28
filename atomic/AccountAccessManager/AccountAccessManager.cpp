/*******************************************************************
*
*  DESCRIPTION: Account Access Manager (of Intenet Online 
*               banking System) Atomic Model 
*
*  AUTHOR: Richard Ying Fang
*
*  DATE: 31/10/2007
*
*******************************************************************/

/** include files **/
#include "AccountAccessManager.h"  
#include "message.h"         // InternalMessage ....
#include "distri.h"          // class Distribution
#include "mainsimu.h"        // class MainSimulator
#include "randlib.h"         // Random numbers library 
#include "strutil.h"         // str2float( ... )
#include <math.h>            // fabs( ... )
#include <stdlib.h>

/*******************************************************************
* Function Name: AccountAccessManager
* Description: constructor
********************************************************************/
AccountAccessManager::AccountAccessManager( const string &name )
: Atomic( name )
, login( addInputPort( "login" ) )
, ian( addInputPort( "ian" ) )
, logout( addOutputPort( "logout" ) )
, van( addOutputPort( "van" ) )
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
* Description: the AccountAccessManager receives login , or invalid
*              account number(ian) notification
********************************************************************/
Model &AccountAccessManager::externalFunction( const ExternalMessage &msg )
{
  if ( this->state() == passive )
  {
    if (msg.port() == login && out_of_session )   // user just login to this session
     {
       login_status = 1;
       ian_status = 0;
        // get a random number of 6 digits to be our card number
        randAccountNumber =  ((double)rand()/(double)RAND_MAX ) * 1000000;
        holdIn( active, Time( static_cast<float>( fabs( distribution().get() ) ) ) ) ;
     }
    if (msg.port() == ian && !out_of_session)   //an ian is received, but user still in the session
     {
       ian_status = 1;
	   login_status = 1;
	   
        // get a random number of 6 digits to be our card number
       randAccountNumber =  ((double)rand()/(double)RAND_MAX ) * 1000000;
       holdIn( active, Time( static_cast<float>( fabs( distribution().get() ) ) ) ) ;
     }
  }
	return *this ;
}

/*******************************************************************
* Function Name: internalFunction
********************************************************************/
Model &AccountAccessManager::internalFunction( const InternalMessage & )
{
    if ( (login_status == 1) && (ian_status == 0))
    {
        out_of_session = false ;
    }
    else if ( ian_status == 1)
         {
         out_of_session = true;
         }
    passivate();
	return *this;
}

/*******************************************************************
* Function Name: outputFunction
********************************************************************/
Model &AccountAccessManager::outputFunction( const InternalMessage &msg )
{

      if ( (login_status == 1) && (ian_status == 0) )
        {
         account_number_enter = (int) randAccountNumber;
         sendOutput( msg.time(), van, account_number_enter );
        
        }
      else if ((ian_status == 1) && (login_status == 1) )
          //received ian request, and logout
        {
         sendOutput( msg.time(), logout , 1 );
         
         }
	return *this;
}

AccountAccessManager::~AccountAccessManager()
{
	delete dist;
}
