function [ bv, u, e, t ] = Ping_Matti( Kp, TI, TD, bv, dT, N)

%Kp: F�rst�rkningsv�rdet som relgera felv�rdet e
%TI: Best�mmer hastigheten p� intergreriingen
%TD: Hur snabbt felet ska deriveras
%bv: b�rv�rdet
%N: antalet samples.
%dT: samplingstiden

%Bluetooth modulen
BT = Bluetooth('RNBT-CCED', 1) %RNTB-CCED
fopen(BT);


PR_array = zeros(1,N);%Arrayer som lagrar avst�ndet pingis bollen har
t = zeros(1,N); %Array som h�ller koll p� antalet samples
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

%N�r data b�rja att s�ndas s� brytts den h�r while loopen och programmet g�r vidare
while(BT.BytesAvailable == 0)
end
lo = 4
while(i < N) 

  start = cputime; %startar en timer f�r att kunna m�ta tiden f�r en loop
    if ok <0 %testar om samplingen �r f�r kort
         %i sampling time too short!
        disp('samplingstiden �r f�r lite! �k v�rdet f�r Ts');
        return
    end
%Tar emot sensor v�rderna ifr�n Arduinot och lagrar v�rderna i arrays    
PR = fscanf(BT);    
PR_array(i) = str2double(PR); 

u_temp = fscanf(BT);    
u(i) = str2double(u_temp) ;

e_temp = fscanf(BT);    
e(i) = str2double(e_temp) ;

%Plottar ut sensor v�rderna
plot(t,PR_array,'r--',t, u, 'b--',t, e, 'g--' );

t(i) = i;
 elapsed=cputime-start; %r�knar �tg�ngen tid i sekunder
    ok=(dT-elapsed); % sparar tidsmarginalen i ok
    
    pause(ok); %pausar resterande samplingstid
    i = i+1;
end 

%Plottar en l�slig hur de fyra sensor v�rderna har betet sig under 100 sekunder
plot(t,PR_array,'r--',t, u, 'b--',t, e, 'g--');
xlabel('Samples ')
ylabel('0-1023 I Bitar')
title('Sensor_plott')
legend('PR', 'u','e' )


fclose(BT);

end

