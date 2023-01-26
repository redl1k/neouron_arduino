////
//СЕТЬ КОХОНЕНА. ПРЯМОЕ РАСПРОСТРАНЕНИЕ СИГНАЛА​
//24.01
////

//Входные данные
int8_t DataSensor[] = { 0, 0 };

float input_el[] = { 0.23, 0.11, 0.41 };

float input_neuron[3][3] = {
  { -0.10, -0.34 },
  { 0.34, -0.01 },
  { -0.22, 0.31 },
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

//+Данные
float hidden_layer[] = { -0.40, 0.11 };


void setup() {
  Serial.begin(9600);
}

void loop() {
  //1. Рассчитываем комбинированные вводы для 0-ого скрытого нейрона
  HiddenCombined[0] = (input_el[0] * input_neuron[0][0]) +  //0.23 | -0.10
                      (input_el[1] * input_neuron[1][0]) +  //0.11 |  0.34
                      (input_el[2] * input_neuron[2][0]);   //0.41 | -0.22

  //2. Рассчитываем комбинированные вводы для 1-ого скрытого нейрона
  HiddenCombined[1] = (input_el[0] * input_neuron[0][1]) +  //0.23 | -0.34
                      (input_el[1] * input_neuron[1][1]) +  //0.11 | -0.01
                      (input_el[2] * input_neuron[2][1]);   //0.41 |  0.31

  //3. Применяем функцию активности для 0-ого скрытого нейрона
  ActivityNeuron[0] = Element_Activity(HiddenCombined[0]);

  //4. Применяем функцию активности для 1-ого скрытого нейрона
  ActivityNeuron[1] = Element_Activity(HiddenCombined[1]);

  //5. Расчитываем комбинированный ввод для выхода сети
  OutputCombined = (ActivityNeuron[0] * hidden_layer[0]) + (ActivityNeuron[1] * hidden_layer[1]);
  Serial.println(ActivityNeuron[0]); 0.48
    Serial.println(hidden_layer[0]); -0.40
  Serial.println(ActivityNeuron[1]); 0.51
  Serial.println(hidden_layer[1]); 0.11
  Serial.println("---------");
    Serial.println("---------");
      Serial.println("---------");
  // // //6. Рассчитываем активность для выхода сети
  // ActivityOutputNeuron = Element_Activity(OutputCombined);

  // // //7. Выводим полученные данные
  // Serial.println(ActivityOutputNeuron);
  // Serial.println("----");
  // delay(1000);
}


//Функция активации (прыжковая) - JumpFuntcion
int8_t signFunction(float neuron) {
  if (neuron > 0)
    return 1;

  if (neuron < 0)
    return 0;
}

//Функция Активности Эйлера
float Element_Activity(float val) {
  return 1 / (1 + pow(EULER, -val));
}
