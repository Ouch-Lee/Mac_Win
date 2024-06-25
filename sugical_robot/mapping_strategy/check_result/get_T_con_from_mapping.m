function T_continuum = get_T_con_from_mapping(t3_input, t4_input, t5_input)
A_pre = modified_DH(0, 0, 0, pi/2);
ks_2 = acos( cos(t3_input) * cos(t4_input) );
if t4_input >= 0
    Phi_2 = acos( (cos(t4_input) * sin(t3_input)) / sin(ks_2)) - pi;
else
    Phi_2 = pi -  acos( (cos(t4_input) * sin(t3_input)) / sin(ks_2));
end

if t3_input >= 0
    Delta_x = 3*pi/2 - acos(cos(t3_input)*sin(Phi_2)) ;
else
    Delta_x = acos(cos(t3_input)*sin(Phi_2)) - pi/2;
end

Theta5 = t5_input + Delta_x + Phi_2;
A_Theta5 = modified_DH(0,0,0, Theta5);
T_continuum = A_pre * get_continuum_T(Phi_2, ks_2) * A_Theta5;