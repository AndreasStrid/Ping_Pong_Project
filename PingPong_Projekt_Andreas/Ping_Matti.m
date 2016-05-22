function [ bv, u, e, t ] = Ping_Matti( Kp, TI, TD, bv, dT, N)

%Kp: Förstärkningsvärdet som relgera felvärdet e
%TI: Bestämmer hastigheten på intergreriingen
%TD: Hur snabbt felet ska deriveras
%bv: börvärdet
%N: antalet samples.
%dT: samplingstiden

%Bluetooth modulen
BT = Bluetooth('RNBT-CCED', 1) %RNTB-CCED
fopen(BT);


PR_array = zeros(1,N);%Arrayer som lagrar avståndet pingis bollen har
t = zeros(1,N); %Array som håller koll på antalet samples
u = zeros(1,N);
u_temp = 0;
e = zeros(1,N);
e_temp = 0;

%Loop variabel
i = 1;
%Tids variabel
ok = 0;

%fprintf('%d \n', Kp)
%fprintf('%d \n', TI)
%fprintf('%d \n', TD)
%fprintf('%d \n', bv)
%fprintf('%d \n', dT)

%När data börja att sändas så brytts den här while loopen och programmet går vidare
while(BT.BytesAvailable == 0)
end
lo = 4
while(i < N) 

  start = cputime; %startar en timer för att kunna mäta tiden för en loop
    if ok <0 %testar om samplingen är för kort
         %i sampling time too short!
        disp('samplingstiden är för lite! Ök värdet för Ts');
        return
    end
%Tar emot sensor värderna ifrån Arduinot och lagrar värderna i arrays    
PR = fscanf(BT);    
PR_array(i) = str2double(PR); 

u_temp = fscanf(BT);    
u(i) = str2double(u_temp) ;

e_temp = fscanf(BT);    
e(i) = str2double(e_temp) ;

%Plottar ut sensor värderna
plot(t,PR_array,'r--',t, u, 'b--',t, e, 'g--' );

t(i) = i;
 elapsed=cputime-start; %räknar åtgången tid i sekunder
    ok=(dT-elapsed); % sparar tidsmarginalen i ok
    
    pause(ok); %pausar resterande samplingstid
    i = i+1;
end 

%Plottar en läslig hur de fyra sensor värderna har betet sig under 100 sekunder
plot(t,PR_array,'r--',t, u, 'b--',t, e, 'g--');
xlabel('Samples ')
ylabel('0-1023 I Bitar')
title('Sensor_plott')
legend('PR', 'u','e' )


fclose(BT);

end

