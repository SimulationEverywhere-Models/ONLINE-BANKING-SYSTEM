/*******************************************************************
*
*  DESCRIPTION:  DESCRIPTION: Simulator::registerNewAtomics()
*
*  AUTHOR: Richard Ying Fang
*
*  DATE: 31/10/2007
*
*******************************************************************/

#include "modeladm.h" 
#include "mainsimu.h"
#include "queue.h"                // class Queue
#include "generat.h"             // class Generator
#include "cpu.h"                 // class CPU
// #include "AccountAccessManager.h"        // class AccountAccessManager
#include "AccountNumberVerifier.h"        // class AccountNumberVerifier
#include "BillPaymentManager.h"        // class BillPaymentManager
#include "PasswordVerifier.h"        // class PasswordVerifier
// #include "TransactionProcessManager.h"          // class TransactionProcessManager
#include "transduc.h"             // class Transducer
#include "trafico.h"              // class Trafico


void MainSimulator::registerNewAtomics()
{
	SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<Queue>() , "Queue" ) ;
	SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<Generator>() , "Generator" ) ;
	SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<CPU>() , "CPU" ) ;
   //  SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<AccountAccessManager>() , "AccountAccessManager" ) ;
    SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<AccountNumberVerifier>() , "AccountNumberVerifier" ) ;
    SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<PasswordVerifier>() , "PasswordVerifier" ) ;
    SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<BillPaymentManager>() , "BillPaymentManager" ) ;
  //    SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<TransactionProcessManager>() , "TransactionProcessManager" ) ;
	SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<Transducer>() , "Transducer" ) ;
	SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<Trafico>() , "Trafico" ) ;
}
