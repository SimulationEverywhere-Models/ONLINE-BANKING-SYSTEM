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
#ifndef __TRANSACTIONPROCESSMANAGER_H
#define __TRANSACTIONPROCESSMANAGER_H

/** include files **/
#include "atomic.h"  // class Atomic

/** forward declarations **/
class Distribution ;

/** declarations **/
class TransactionProcessManager: public Atomic
{
	
public:

	// Default constructor
	TransactionProcessManager( const string &name = "TransactionProcessManager" ) ;	 

	// Destructor
	~TransactionProcessManager();					

	virtual string className() const {return "TransactionProcessManager";}

protected:

	Model &initFunction()
	{    
		// current_account_balance = 3000;
        return *this;
    }

	Model &externalFunction( const ExternalMessage & );

	Model &internalFunction( const InternalMessage & );

	Model &outputFunction( const InternalMessage & );

private:

	const Port &VBA_IN ;
	Port &UAB_OUT ;
    Port &LOGOUT;

	Distribution *dist ;

    // int current_account_balance;
    int billAmount;

	Distribution &distribution() {return *dist;}
};	// class TransactionProcessManager


#endif    //__TRANSACTIONPROCESSMANAGER_H
