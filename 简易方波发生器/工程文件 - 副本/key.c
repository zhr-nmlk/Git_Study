#include <REGX52.H>

#define key_input    P3_0    // ���������

#define N_key    0             //�޼�
#define S_key    1             //����
#define D_key    2             //˫��
#define L_key    3             //����

#define key_state_0 0
#define key_state_1 1
#define key_state_2 2   
#define key_state_3 3

unsigned char key_driver(void)
{
    static unsigned char key_state = key_state_0, key_time = 0;
    unsigned char key_press, key_return = N_key;

    key_press = key_input;                  // ������I/O��ƽ

    switch (key_state)
    {
      case key_state_0:                            // ������ʼ̬
        if (!key_press) key_state = key_state_1;  //�������£�״̬ת��������������ȷ��״̬
        break;
      
      case key_state_1:                      // ����������ȷ��̬
        if (!key_press)
        {
             key_time = 0;                   //  
             key_state = key_state_2;   // ������Ȼ���ڰ��£�������ɣ�״̬ת�������¼�ʱ�� 
                                                          // �ļ�ʱ״̬�������صĻ����޼��¼�
        }
        else
             key_state = key_state_0;   // ������̧��ת����������ʼ̬���˴���ɺ�ʵ����� 
                                                          // ��������ʵ�����İ��º��ͷŶ��ڴ������ġ�
        break;
      
      case key_state_2:
        if(key_press)
        {
             key_return = S_key;           // ��ʱ�����ͷţ�˵���ǲ���һ�ζ̲���������S_key
             key_state = key_state_0;   // ת����������ʼ̬
        }
        else if (++key_time >= 100)    // �������£���ʱ��10ms��10msΪ������ѭ��ִ�м����
        {
             key_return = L_key;            // ����ʱ��>1000ms���˰���Ϊ�������������س����¼�
             key_state = key_state_3;   // ת�����ȴ������ͷ�״̬
        }
        break;

      case key_state_3:                 // �ȴ������ͷ�״̬����״ֻ̬�����ް����¼�
        if (key_press) key_state = key_state_0; //�������ͷţ�ת����������ʼ̬
        break;
    }
    return key_return;
}

unsigned char key_read(void)
{
    static unsigned char key_m = key_state_0, key_time_1 = 0;
    unsigned char key_return = N_key,key_temp;
     
    key_temp = key_driver();
     
    switch(key_m)
    {
        case key_state_0:
            if (key_temp == S_key )
            {
                 key_time_1 = 0; // ��1�ε����������أ����¸�״̬�жϺ����Ƿ����˫��
                 key_m = key_state_1;
            }
            else
                 key_return = key_temp;        // �����޼�������������ԭ�¼�
            break;

        case key_state_1:
            if (key_temp == S_key)             // ��һ�ε���������϶�<500ms��
            {
                 key_return = D_key;           // ����˫�����¼����س�ʼ״̬
                 key_m = key_state_0;
            }
            else                                
            {                         // ����500ms�ڿ϶������Ķ����޼��¼�����Ϊ 
                                      // ����>1000ms����1sǰ�Ͳ㷵�صĶ����޼�
                 if(++key_time_1 >= 50)
                 {
                     key_return = S_key; //500ms��û���ٴγ��ֵ����¼���������һ�� 
                                         // �ĵ����¼�
                     key_m = key_state_0;   // ���س�ʼ״̬
                 }
             }
             break;
    }
    return key_return;
} 