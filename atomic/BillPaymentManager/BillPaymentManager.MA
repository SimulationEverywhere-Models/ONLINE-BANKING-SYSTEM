[top]
components : bpm@BillPaymentManager
out : VBA
out : IBA
in : VPN
in : IBA

Link : VPN  VPN_IN@bpm
Link : IBA  IBA_IN@bpm
Link : VBA_OUT@bpm VBA
Link : IBA_OUT@bpm IBA


[bpm]
distribution : normal
mean : 4
deviation : 2 