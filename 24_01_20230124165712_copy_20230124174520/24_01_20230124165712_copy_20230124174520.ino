////
//СЕТЬ КОХОНЕНА. ПРЯМОЕ РАСПРОСТРАНЕНИЕ СИГНАЛА​
//24.01 
////

//Входные данные
int8_t DataSensor[] = { 0, 0 };

float intput_el[] = {0.23, 0.11, 0.41};

float intput_neuron[3][3] = {
  {-0.10, -0.34},
  {0.34, -0.01},
  {-0.22, 0.31},
};


//Элемент смещения
int8_t Bias1 = 1;
int8_t Bias2 = 1;

//Комбинированные вводы для скрытых нейронов
float HiddenCombined[2];

//Активности нейронов скрытого слоя
float ActivityNeuron[2];

//Комбинированный для выхода сети
float OutputCombined;

//Активность выходного нейрона
int8_t ActivityOutputNeuron;

//Вводим данные, которые в дальнейшем будут обрабатываться
////Весовые коэффиценты от входного слоя к скрытому
float InputWeight[3][2] = {
  { 0.23, 0.10 },
  { -1, -1 },    //Строка + столбец
  { 1.5, 0.5 },  //2 элемент 1.5 .. 2-строчка 1 столбец = 0.5
};

//Весовые коэффиценты от скрытого слоя к выходу сети
float OutputWeight[] = { 1, -1, -0.5 };


void setup() {
  Serial.begin(9600);
}

void loop() {
//1. Рассчитываем комбинированные вводы для 0-ого скрытого нейрона
  HiddenCombined[0] = (input_el[0] * input_neuron[0][0] ) + 
                      (input_el[1] * input_neuron[1][0] ) +
                      (input_el[2] * input_neuron[2][0] );

//2. Рассчитываем комбинированные вводы для 1-ого скрытого нейрона
  HiddenCombined[1] = (input_el[0] * input_neuron[0][0] ) + 
                      (input_el[1] * input_neuron[1][1] ) +
                      (input_el[2] * input_neuron[2][2] );

Serial.println(HiddenCombined[0]);
Serial.println(HiddenCombined[1]);

// flaot Elemnt_Activity (float val) {
//   return 1/( 1 + pow (EULER), -val));
// }


//Функция активации (прыжковая) - JumpFuntcion
int8_t signFunction(float neuron) {
  if (neuron > 0)
    return 1;

  if (neuron < 0)
    return 0;
}