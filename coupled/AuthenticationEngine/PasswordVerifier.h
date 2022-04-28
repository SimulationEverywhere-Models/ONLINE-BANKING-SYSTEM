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
#ifndef __PASSWORDVERIFIER_H
#define __PASSWORDVERIFIER_H

/** include files **/
#include "atomic.h"  // class Atomic

/** forward declarations **/
class Distribution ;

/** declarations **/
class PasswordVerifier: public Atomic
{
	
public:

	// Default constructor
	PasswordVerifier( const string &name = "PasswordVerifier" ) ;	 

	// Destructor
	~PasswordVerifier();					

	virtual string className() const {return "PasswordVerifier";}

protected:

	Model &initFunction()
	{    
		randPasswordNumber = 0;
        return *this;
    }

	Model &externalFunction( const ExternalMessage & );

	Model &internalFunction( const InternalMessage & );

	Model &outputFunction( const InternalMessage & );

private:
	const Port &VAN_IN ;
	const Port &IVPN_IN;
	Port &VPN_OUT ;
    Port &IVPN_OUT;

	Distribution *dist ;
    int randPasswordNumber; // 0 or 1

	Distribution &distribution() {return *dist;}
};	// class PasswordVerifier


#endif    //__PASSWORDVERIFIER_H
