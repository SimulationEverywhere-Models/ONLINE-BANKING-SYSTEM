/*******************************************************************
*
*  DESCRIPTION: Password Verifier (of Intenet Online 
*               banking System) Atomic Model 
*
*  AUTHOR: Richard Ying Fang
*
*  DATE: 31/10/2007
*
*******************************************************************/

/** include files **/

#include "PasswordVerifier.h"  
#include "message.h"         // InternalMessage ....
#include "distri.h"          // class Distribution
#include "mainsimu.h"        // class MainSimulator
#include "randlib.h"         // Random numbers library 
#include "strutil.h"         // str2float( ... )
#include <math.h>            // fabs( ... )
#include <stdlib.h>

/*******************************************************************
* Function Name: PasswordVerifier
* Description: constructor
********************************************************************/
PasswordVerifier::PasswordVerifier( const string &name )
: Atomic( name )
, VAN_IN( addInputPort( "VAN_IN" ) )
, IVPN_IN( addInputPort( "IVPN_IN" ) )
, VPN_OUT( addOutputPort( "VPN_OUT" ) )
, IVPN_OUT( addOutputPort( "IVPN_OUT" ) )
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
* Description: the PasswordVerifier receives valid account number input 
* 			   invalid Password Number
********************************************************************/
Model &PasswordVerifier::externalFunction( const ExternalMessage &msg )
{
  if ( this->state() == passive)
   {

    if ( (msg.port() == VAN_IN ) && (msg.port() != IVPN_IN  )  ) 
     {
        holdIn( active, Time( static_cast<float>( fabs( distribution().get() ) ) ) ) ;            	
        // get a random number of 0 or 1
    	randPasswordNumber =  rand()%2 ;
     }
    if (msg.port() == IVPN_IN )   
     {
       holdIn( active, Time( static_cast<float>( fabs( distribution().get() ) ) ) ) ;
        // get a random number of 0 or 1
     	randPasswordNumber =  rand()%2 ;
     }
   }
	return *this ;
}

/*******************************************************************
* Function Name: internalFunction
********************************************************************/
Model &PasswordVerifier::internalFunction( const InternalMessage & )
{
	passivate();
	return *this;
}

/*******************************************************************
* Function Name: outputFunction
********************************************************************/
Model &PasswordVerifier::outputFunction( const InternalMessage &msg )
{
      if ( randPasswordNumber == 1 )
         sendOutput( msg.time(), VPN_OUT, 1 );
      else
        {
         sendOutput( msg.time(), IVPN_OUT, 1 );
         }
	return *this;
}

PasswordVerifier::~PasswordVerifier()
{
	delete dist;
}
