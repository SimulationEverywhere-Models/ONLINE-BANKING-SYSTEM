[top]
components : aam@AccountAccessManager
out : logout_OUT
out : van_OUT
in : login_IN
in : ian_IN
 
Link : ian_IN ian@aam
Link : login_IN login@aam
Link : van@aam van_OUT
Link : logout@aam logout_OUT


[aam]
distribution : normal
mean : 4
deviation : 2 
