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
#ifndef __ACCOUNTACCESSMANAGER_H
#define __ACCOUNTACCESSMANAGER_H

/** include files **/
#include "atomic.h"  // class Atomic

/** forward declarations **/
class Distribution ;

/** declarations **/
class AccountAccessManager: public Atomic
{
	
public:

    // Default constructor 
	AccountAccessManager( const string &name = "AccountAccessManager" ) ;	 

    // Destructor
	~AccountAccessManager();					

	virtual string className() const {return "AccountAccessManager";}

protected:

	Model &initFunction()
	{   
		login_status =0;
		ian_status=0;
		account_number_enter = 0;
		out_of_session = true;
        
        return *this;
    }

	Model &externalFunction( const ExternalMessage & );

	Model &internalFunction( const InternalMessage & );

	Model &outputFunction( const InternalMessage & );

private:

	const Port &login ;
    const Port &ian ; //indicate an invalid account number entered
 	Port &logout ;    
    Port &van;  //indicate a valid account number has been entered

    int account_number_enter, login_status, ian_status;
    bool out_of_session;   // TRUE mean there is no invalid acount number reported
	Distribution *dist ;

    double randAccountNumber;
	Distribution &distribution() {return *dist;}
};	// class AccountAccessManager


#endif    //__ACCOUNTACCESSMANAGER_H
