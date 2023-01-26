//Сеть Кохонена для вычисления операции XOR

//Входные данные
int8_t DataSensor[] = { 1, 0 };

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
  { -1, -1 },
  { -1, -1 },    //Строка + столбец
  { 1.5, 0.5 },  //2 элемент 1.5 .. 2-строчка 1 столбец = 0.5
};

//Весовые коэффиценты от скрытого слоя к выходу сети
float OutputWeight[] = { 1, -1, 0.5 };


void setup() {
  Serial.begin(9600);
}

void loop() {
//1. Рассчитываем комбинированные вводы для 0-ого скрытого нейрона
  HiddenCombined[0] = (DataSensor[0] * InputWeight[0][0] ) + 
                      (DataSensor[1] * InputWeight[1][0] ) +
                      ( Bias1 * InputWeight[2][0] );

//2. Рассчитываем комбинированные вводы для 1-ого скрытого нейрона
  HiddenCombined[1] = (DataSensor[0] * InputWeight[0][1] ) + 
                      (DataSensor[1] * InputWeight[1][1] ) +
                      ( Bias1 * InputWeight[2][1] );

//3. Применяем функцию активности для 0-ого скрытого нейрона
  ActivityNeuron[0] = signFunction(HiddenCombined[0]);

//4. Применяем функцию активности для 1-ого скрытого нейрона
  ActivityNeuron[1] = signFunction(HiddenCombined[1]);

//5. Расчитываем комбинированный ввод для выхода сети
 OutputCombined = (ActivityNeuron[0] * OutputWeight[0]) +
                  (ActivityNeuron[1] * OutputWeight[1]) + 
                  ( Bias2 * OutputWeight[2] );

//6. Рассчитываем активность для выхода сети
 ActivityOutputNeuron = signFunction( OutputCombined );

//7. Выводим полученные данные
 Serial.println( ActivityOutputNeuron) ;
}


//Функция активации (прыжковая) - JumpFuntcion
int8_t signFunction(float neuron) {
  if (neuron > 0)
    return 1;

  if (neuron < 0)
    return 0;
}
