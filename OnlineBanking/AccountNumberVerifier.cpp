/*******************************************************************
*
*  DESCRIPTION: Account Number Verifier (of Intenet Online 
*               banking System) Atomic Model 
*
*  AUTHOR: Richard Ying Fang
*
*  DATE: 31/10/2007
*
*******************************************************************/

/** include files **/

#include "AccountNumberVerifier.h"  // base header
#include "mainsimu.h"      // class MainSimulator
#include "distri.h"        // class Distribution
#include "message.h"       // InternalMessage ....
#include "randlib.h"         // Random numbers library
#include "strutil.h"       // str2float( ... )
#include <math.h>            // fabs( ... )
#include <stdlib.h>

/*******************************************************************
* Function Name: AccountNumberVerifier
* Description: constructor
********************************************************************/
AccountNumberVerifier::AccountNumberVerifier( const string &name )
: Atomic( name )
, AccountNumber_IN( addInputPort( "AccountNumber_IN" ) )
, logout_OUT( addOutputPort( "logout_OUT" ) )
, ValidAccountNumber_OUT( addOutputPort( "ValidAccountNumber_OUT" ) )
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
* Description: the AccountNumberVerifier receives the AccountNumber_IN as input
********************************************************************/
Model &AccountNumberVerifier::externalFunction( const ExternalMessage &msg )
{
  if ( this->state() == passive)
  {
    if (msg.port() == AccountNumber_IN )
     {
       	// account_number_is_entered = 1;
     
		holdIn( active, Time( static_cast<float>( fabs( distribution().get() ) ) ) ) ;
    	
    	// get a random number of 0 or 1
    	randAccountNumberValid =  rand()%2 ;
    
     }
  }
	return *this ;
}

/*******************************************************************
* Function Name: internalFunction
********************************************************************/
Model &AccountNumberVerifier::internalFunction( const InternalMessage & )
{
	passivate();
	return *this;
}

/*******************************************************************
* Function Name: outputFunction
********************************************************************/
Model &AccountNumberVerifier::outputFunction( const InternalMessage &msg )
{

      if ( randAccountNumberValid == 1 )
        {         
         sendOutput( msg.time(), ValidAccountNumber_OUT, 1 );
        }
      else
        {         
         sendOutput( msg.time(), logout_OUT , 1 );
         }
	return *this;
}

AccountNumberVerifier::~AccountNumberVerifier()
{
	delete dist;
}
