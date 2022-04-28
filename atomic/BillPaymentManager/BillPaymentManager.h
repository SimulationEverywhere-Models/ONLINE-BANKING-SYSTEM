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
#ifndef __BILLPAYMENTMANAGER_H
#define __BILLPAYMENTMANAGER_H

/** include files **/
#include "atomic.h"  // class Atomic

/** forward declarations **/
class Distribution ;

/** declarations **/
class BillPaymentManager: public Atomic
{
// friend class TransactionProcessManager;	
public:

	// Default constructor
	BillPaymentManager( const string &name = "BillPaymentManager" ) ;	 

	// Destructor
	~BillPaymentManager();					

	virtual string className() const {return "BillPaymentManager";}

protected:

	Model &initFunction()
	{    
		randBilAmount = 0;
		current_account_balance = 3000;
        return *this;
    }

	Model &externalFunction( const ExternalMessage & );

	Model &internalFunction( const InternalMessage & );

	Model &outputFunction( const InternalMessage & );

private:
	const Port &VPN_IN ;
	const Port &IBA_IN;
	Port &VBA_OUT ;
    Port &IBA_OUT;

	Distribution *dist ;
    int randBilAmount; // 1 - 4000
       int current_account_balance;

	Distribution &distribution() {return *dist;}
};	// class BillPaymentManager


#endif    //__BILLPAYMENTMANAGER_H
