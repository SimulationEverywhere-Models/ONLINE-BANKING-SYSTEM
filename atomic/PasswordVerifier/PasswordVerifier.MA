[top]
components : pv@PasswordVerifier
out : VPN
out : IVPN
in : VAN
in : IVPN

Link : VAN  VAN_IN@pv
Link : IVPN  IVPN_IN@pv
Link : VPN_OUT@pv VPN
Link : IVPN_OUT@pv IVPN


[pv]
distribution : normal
mean : 4
deviation : 2 