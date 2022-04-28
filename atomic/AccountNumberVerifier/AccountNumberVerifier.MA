[top]
components : anv@AccountNumberVerifier
out : ValidAccountNumber
out : logout 
in : AccountNumber 

Link : AccountNumber  AccountNumber_IN@anv
Link : ValidAccountNumber_OUT@anv ValidAccountNumber
Link : logout_OUT@anv logout


[anv]
distribution : normal
mean : 4
deviation : 2 