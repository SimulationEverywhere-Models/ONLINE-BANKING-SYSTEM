[top]
components : AE aam@AccountAccessManager tpm@TransactionProcessManager
out : ab
out : logout
in : login

Link : login login@aam

Link : logout@aam logout

Link : UAB_OUT@tpm ab

Link : LOGOUT@tpm ian@aam

Link : logout@AE ian@aam

Link : van@aam an@AE

Link : ba@AE VBA_IN@tpm

[AE]
components : bpm@BillPaymentManager pv@PasswordVerifier anv@AccountNumberVerifier
out : ba
out : logout
in : an

Link : an AccountNumber_IN@anv
Link : logout_OUT@anv logout
Link : ValidAccountNumber_OUT@anv VAN_IN@pv
Link : IVPN_OUT@pv IVPN_IN@pv
Link : VPN_OUT@pv VPN_IN@bpm
Link : IBA_OUT@bpm IBA_IN@bpm
Link : VBA_OUT@bpm ba




[bpm]
distribution : normal
mean : 4
deviation : 2 

[pv]
distribution : normal
mean : 4
deviation : 2 

[anv]
distribution : normal
mean : 4
deviation : 2 

[aam]
distribution : normal
mean : 2
deviation : 1 

[tpm]
distribution : normal
mean : 2
deviation : 1 