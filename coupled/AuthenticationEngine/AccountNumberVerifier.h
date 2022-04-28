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
#ifndef __ACCOUNTNUMBERVERIFIER_H
#define __ACCOUNTNUMBERVERIFIER_H

/** include files **/
#include "atomic.h"  // class Atomic

/** forward declarations **/
class Distribution ;

/** declarations **/
class AccountNumberVerifier: public Atomic
{
	
public:

	// Default constructor
	AccountNumberVerifier( const string &name = "AccountNumberVerifier" ) ;	 

	// Destructor
	~AccountNumberVerifier();					

	virtual string className() const {return "AccountNumberVerifier";}

protected:

	Model &initFunction()
	{   
		randAccountNumberValid = 0;                      
       
       	return *this;
                      
    }

	Model &externalFunction( const ExternalMessage & );

	Model &internalFunction( const InternalMessage & );

	Model &outputFunction( const InternalMessage & );

private:

	const Port &AccountNumber_IN ;
	Port &logout_OUT ;
    Port &ValidAccountNumber_OUT;
    
    // int   pin, pin_entered, amnt_entered, amnt;
    // int account_number_is_entered;
    
	Distribution *dist ;
    int randAccountNumberValid;

	Distribution &distribution(){return *dist;}
};	// class AccountNumberVerifier


#endif    //__ACCOUNTNUMBERVERIFIER_H
