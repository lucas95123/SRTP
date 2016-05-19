int pinLed = 13;//��������LED�����ֿڣ�������ͨ�����ڷ�������ʱ������LED������ر�LED
boolean sendFlag = false;//ָʾ�Ƿ�����ͨ�����ڷ�������
boolean readCompleted = false;//ָʾ�Ƿ���ɶ�ȡ��������
String serialString = "";//�������ݻ����ַ���
 
//Author��Alex Leo, Email:conexpress@qq.com, Blog:http://conexpress.cnblogs.com/
//�ο�:http://arduino.cc/en/Reference/Serial
void setup()
{
  pinMode(pinLed,OUTPUT);
  Serial.begin(9600);
  serialString.reserve(200);//��ʼ���ַ���
}
 
void loop()
{
  int lightValue = analogRead(A0);//��A0�ڶ�ȡ���ߴ�������ֵ
  if(readCompleted)//�жϴ����Ƿ���յ����ݲ���ɶ�ȡ
  {
    Serial.print("read value:");
    Serial.println(serialString);//����ȡ������Ϣ���͸�����
    if(serialString == "serial start")//����ȡ������Ϣ��"serial start"ʱ�����÷��ͱ�־����Ϊtrue
    {
      sendFlag = true;
    }
    else if(serialString == "serial stop")//����ȡ������Ϣ��"serial stop"ʱ�����÷��ͱ�־����Ϊfalse
    {
      sendFlag = false;
    }
    serialString = "";
    readCompleted = false;
  }
 
  if(sendFlag)//�������ͨ�����ڷ������ݣ������LED���������ݣ�����ر�LED
  {
    digitalWrite(pinLed, HIGH);
    Serial.print("light value:");
    Serial.println(lightValue);
  }
  else
  {
    digitalWrite(pinLed, LOW);
  }
  delay(1000);//��ʱ1000ms
}
 
void serialEvent()//�����¼����������ο�:http://arduino.cc/en/Tutorial/SerialEvent
{
  while(Serial.available())//�ο�://arduino.cc/en/Serial/Available
  {
    char inChar = (char)Serial.read();
    if(inChar != '\n')//�Ի��з���Ϊ��ȡ������־
    {
      serialString += inChar;
    }
    else
    {
      readCompleted = true;
    }
  }
}