
//Biblioteca responsável pela comunicação I2C do projeto
#include "Wire.h"
//Biblioteca responsável pelo LCD
#include<LiquidCrystal.h>
#define DS1307_ADDRESS 0x68
 



byte num,zero=0x00;
int a=1,c=1,opc=15,count=0,unidade,dezena,numero,count2=0,segundos,minutos,horas,ano,mes,dia,prog=1,diadasemana=0;

LiquidCrystal lcd (8,7,5,4,3,2);







void setup() {
  Serial.begin(9600);
  Wire.begin();
  lcd.begin(16,2);
  inicio();
}


void inicio()
{
  Serial.println("O que deseja fazer?");
  Serial.println("0 - Configurar Data e Hora");
  Serial.println("1 - Visualizar Data e Hora");
  Serial.println("2 - Pausar Exibicao");

}
void loop() 
{
  if(prog==1)
  recebermenu();


  switch(opc)
  {
      
   case 0:
   selecionarhora();
    break;

    case 1:
    MostrarRelogio();
    break;

    case 2:
    while(c==1){
    MostrarRelogio();c++;}
    break;
  }
  
    
  }

void MostrarRelogio()
{
  Wire.beginTransmission(DS1307_ADDRESS);
  Wire.write(zero);
  Wire.endTransmission();
  Wire.requestFrom(DS1307_ADDRESS, 7);
  segundos = ConverteparaDecimal(Wire.read());
  minutos = ConverteparaDecimal(Wire.read());
  horas = ConverteparaDecimal(Wire.read() & 0b111111);
  diadasemana = ConverteparaDecimal(Wire.read()); 
  dia = ConverteparaDecimal(Wire.read());
  mes = ConverteparaDecimal(Wire.read());
  ano = ConverteparaDecimal(Wire.read());

  lcd.setCursor(0,0);
  lcd.print("     ");
  Serial.print("     ");
  // Acrescenta o 0 (zero) se a hora for menor do que 10
  if (horas <10){
    lcd.print("0");Serial.print("0");}
  lcd.print(horas);
  Serial.print(horas);
  Serial.print(":");
  lcd.print(":");
  // Acrescenta o 0 (zero) se minutos for menor do que 10
  if (minutos < 10){
     lcd.print("0");Serial.print("0");}
  lcd.print(minutos);
  Serial.print(minutos);
  Serial.print(":");
  lcd.print(":");

  if(segundos < 10){
  lcd.print("0");Serial.print("0");}
  lcd.print(segundos);
  Serial.print(segundos);
  Serial.print("      ");
  
  lcd.setCursor(2,1);
  switch(diadasemana)
    {
      case 0:lcd.print("Dom");Serial.print("Dom ");
      break;
      case 1:lcd.print("Seg");Serial.print("Seg ");
      break;
      case 2:lcd.print("Ter");Serial.print("Ter ");
      break;
      case 3:lcd.print("Quar");Serial.print("Quar ");
      break;
      case 4:lcd.print("Qui");Serial.print("Qui ");
      break;
      case 5:lcd.print("Sex");Serial.print("Sex ");
      break;
      case 6:lcd.print("Sab");Serial.print("Sab ");
    }
    lcd.setCursor(6,1);
    // Acrescenta o 0 (zero) se dia do mes for menor do que 10
    if (dia < 10){
      lcd.print("0");Serial.print("0");}
    lcd.print(dia);
    Serial.print(dia);
    Serial.print("/");
    lcd.print("/");
    // Acrescenta o 0 (zero) se mes for menor do que 10
    if (mes < 10){
    lcd.print("0");Serial.print("0");}
    lcd.print(mes);
    Serial.print(mes);
    Serial.print("/");
    Serial.print("20");
    Serial.println(ano);
    lcd.print("/");
    lcd.print("20");
    lcd.print(ano);
    delay(1000);
}

void selecionarhora()
{
  if(count==0)
    {
      if(count2==0)
      {
      Serial.println("Digite a unidade do segundo");
      count2=1;
      }
      recebernumero1();
    }
    else if(count==1)
    {
      if(count2==0)
      {
      Serial.println("Digite a dezena do segundo");
      count2=1;
      }
      recebernumero2();
    }
    else if(count==2)
    {
      
      if(count2==0)
      juntarnumero();
      segundos=numero;
      count2=0;
    }  
    else if(count==3)
    {
      
      if(count2==0)
      {
      Serial.println("Digite a unidade do minuto");
      count2=1;
      }
      recebernumero1();
    }
    else if(count==4)
    {
      
      if(count2==0)
      {
      Serial.println("Digite a dezena do minuto");
      count2=1;
      }
      recebernumero2();
    }
    else if(count==5)
    {
      
      if(count2==0)
      juntarnumero();
      minutos=numero;
      count2=0;
    }  
    else if(count==6)
    {
      
      if(count2==0)
      {
      Serial.println("Digite a unidade da hora");
      count2=1;
      }
      recebernumero1();
    }
    else if(count==7)
    {
      
      if(count2==0)
      {
      Serial.println("Digite a dezena da hora");
      count2=1;
      }
      recebernumero2();
    }
    else if(count==8 )
    {
      
      if(count2==0)
      juntarnumero();
      horas=numero;
      count2=0;
    }  
    else if(count==9)
    {
      if(count2==0)
      {
      Serial.print("HORA ESTABELECIDA:  ");
      Serial.print(horas);
      Serial.print(":");
      Serial.print(minutos);
      Serial.print(":");
      Serial.println(segundos);
      count++;
      }
      count2==0;
    }  
    else if(count==10)
    {
      
      if(count2==0)
      {
      Serial.println("Digite a unidade do ano");
      count2=1;
      }
      recebernumero1();
    }
    else if(count==11)
    {
      
      if(count2==0)
      {
      Serial.println("Digite a dezena do ano");
      count2=1;
      }
      recebernumero2();
    }
    else if(count==12)
    {
      
      if(count2==0)
      juntarnumero();
      ano=numero;
      count2=0;
    } 
    else if(count==13)
    {
      
      if(count2==0)
      {
      Serial.println("Digite a unidade do mes");
      count2=1;
      }
      recebernumero1();
    }
    else if(count==14)
    {
      
      if(count2==0)
      {
      Serial.println("Digite a dezena do mes");
      count2=1;
      }
      recebernumero2();
    } 
    else if(count==15)
    {
      
      if(count2==0)
      juntarnumero();
      mes=numero;
      count2=0;
    } 
    else if(count==16)
    {
      
      if(count2==0)
      {
      Serial.println("Digite a unidade do dia do mes");
      count2=1;
      }
      recebernumero1();
    } 
    else if(count==17)
    {
      
      if(count2==0)
      {
      Serial.println("Digite a dezena do dia do mes");
      count2=1;
      }
      recebernumero2();
    } 
    else if(count==18)
    {
      
      if(count2==0)
      diadomes();
      dia=numero;
      count2=0;
    }
    else if(count==19)
    {
      if(count2==0)
      {
      verdataehora();
      count++;
      }
      count2==0;
    }  
    else if(count==20)
    {
      Wire.beginTransmission(DS1307_ADDRESS);
      Wire.write(zero); 
  
      Wire.write(ConverteParaBCD(segundos));
      Wire.write(ConverteParaBCD(minutos));
      Wire.write(ConverteParaBCD(horas));
      Wire.write(ConverteParaBCD(diadasemana));
      Wire.write(ConverteParaBCD(dia));
      Wire.write(ConverteParaBCD(mes));
      Wire.write(ConverteParaBCD(ano));
      Wire.write(zero);
      Wire.endTransmission();
      count++; 
    }
    else if(count==21)
    {
      MostrarRelogio();
    }
}

void recebernumero1()
{
  if(Serial.available())
  {
    byte num = Serial.read();
    if((num>=48)&&(num<=57))
    {
      num=num-48;
      unidade=num;
      count++;
      count2=0;  
    }  
  }
}

void recebernumero2()
{
  if(Serial.available())
  {
    byte num = Serial.read();
    if((num>=48)&&(num<=57))
    {
      num=num-48;
      dezena=num;
      count++;
      count2=0;  
    }  
  }
}
void juntarnumero()
{
  
  numero=(dezena*10)+unidade;
  if(((numero>59)&&(count<6))||((count>5)&&(count<10)&&(numero>23))||((count>12)&&(numero>12)))
  {
    if(count<10)
    {
    Serial.println("Horario Invalido");
    count=0;
    }
    else if (count>=10)
    {
      Serial.println("Data Invalida");
      count=10;
    }
  }
  else 
  {
        if(numero<10)
        {
        Serial.print("0");
         Serial.println(numero);
          count2=1;
          count++;
        }
        else 
        {
          Serial.println(numero);
          count2=1;
          count++;
        }
  }
}

void diadomes()
{
  numero=(dezena*10)+unidade;
  if(mes==1)
  {
    if(numero>31)
    {
      Serial.println("Dia Invalido");
      count=10;
    }
    else
    {
        if(numero<10)
        {
        Serial.print("0");
         Serial.println(numero);
          count2=1;
          count++;
        }
        else 
        {
          Serial.println(numero);
          count2=1;
          count++;
        }
    }
  }
  else if(mes==2)
  {
    if(numero>28)
    {
      Serial.println("Dia Invalido");
      count=10;
    }
    else
    {
        if(numero<10)
        {
        Serial.print("0");
         Serial.println(numero);
          count2=1;
          count++;
        }
        else 
        {
          Serial.println(numero);
          count2=1;
          count++;
        }
    }
  }
  else if(mes==3)
  {
    if(numero>31)
    {
      Serial.println("Dia Invalido");
      count=10;
    }
    else
    {
        if(numero<10)
        {
        Serial.print("0");
         Serial.println(numero);
          count2=1;
          count++;
        }
        else 
        {
          Serial.println(numero);
          count2=1;
          count++;
        }
    }
  }
  else if(mes==4)
  {
    if(numero>30)
    {
      Serial.println("Dia Invalido");
      count=10;
    }
    else
    {
        if(numero<10)
        {
        Serial.print("0");
         Serial.println(numero);
          count2=1;
          count++;
        }
        else 
        {
          Serial.println(numero);
          count2=1;
          count++;
        }
    }
  }
  else if(mes==5)
  {
    if(numero>31)
    {
      Serial.println("Dia Invalido");
      count=10;
    }
    else
    {
        if(numero<10)
        {
        Serial.print("0");
         Serial.println(numero);
          count2=1;
          count++;
        }
        else 
        {
          Serial.println(numero);
          count2=1;
          count++;
        }
    }
  }
  else if(mes==6)
  {
    if(numero>30)
    {
      Serial.println("Dia Invalido");
      count=10;
    }
    else
    {
        if(numero<10)
        {
        Serial.print("0");
         Serial.println(numero);
          count2=1;
          count++;
        }
        else 
        {
          Serial.println(numero);
          count2=1;
          count++;
        }
    }
  }
  else if(mes==7)
  {
    if(numero>31)
    {
      Serial.println("Dia Invalido");
      count=10;
    }
    else
    {
        if(numero<10)
        {
        Serial.print("0");
         Serial.println(numero);
          count2=1;
          count++;
        }
        else 
        {
          Serial.println(numero);
          count2=1;
          count++;
        }
    }
  }
  else if(mes==8)
  {
    if(numero>31)
    {
      Serial.println("Dia Invalido");
      count=10;
    }
    else
    {
        if(numero<10)
        {
        Serial.print("0");
         Serial.println(numero);
          count2=1;
          count++;
        }
        else 
        {
          Serial.println(numero);
          count2=1;
          count++;
        }
    }
  }
  else if(mes==9)
  {
    if(numero>30)
    {
      Serial.println("Dia Invalido");
      count=10;
    }
    else
    {
        if(numero<10)
        {
        Serial.print("0");
         Serial.println(numero);
          count2=1;
          count++;
        }
        else 
        {
          Serial.println(numero);
          count2=1;
          count++;
        }
    }
  }
  else if(mes==10)
  {
    if(numero>31)
    {
      Serial.println("Dia Invalido");
      count=10;
    }
    else
    {
        if(numero<10)
        {
        Serial.print("0");
         Serial.println(numero);
          count2=1;
          count++;
        }
        else 
        {
          Serial.println(numero);
          count2=1;
          count++;
        }
    }
  }
  else if(mes==11)
  {
    if(numero>30)
    {
      Serial.println("Dia Invalido");
      count=10;
    }
    else
    {
        if(numero<10)
        {
        Serial.print("0");
         Serial.println(numero);
          count2=1;
          count++;
        }
        else 
        {
          Serial.println(numero);
          count2=1;
          count++;
        }
    }
  }
  else if(mes==12)
  {
    if(numero>31)
    {
      Serial.println("Dia Invalido");
      count=10;
    }
    else
    {
        if(numero<10)
        {
        Serial.print("0");
         Serial.println(numero);
          count2=1;
          count++;
        }
        else 
        {
          Serial.println(numero);
          count2=1;
          count++;
        }
    }
  }
}


void recebermenu()
{
  
  if(Serial.available())
  {
     opc = Serial.read();
    if((opc>47)&&(opc<51))
    {
     
      opc=opc-48;
      prog=0;
    }
   }  
}

void verdataehora()
{
      Serial.print("DATA:  ");
      Serial.print(dia);
      Serial.print("/");
      Serial.print(mes);
      Serial.print("/");
      Serial.println(ano);
      Serial.print("HORA:  ");
      Serial.print(horas);
      Serial.print(":");
      Serial.print(minutos);
      Serial.print(":");
      Serial.println(segundos);
}

byte ConverteParaBCD(byte val)
{ 
  //Converte o número de decimal para BCD
  return ( (val/10*16) + (val%10) );
}

byte ConverteparaDecimal(byte val)  
{ 
  //Converte de BCD para decimal
  return ( (val/16*10) + (val%16) );
}
