//вроде как ассинхронная под 5 картинок

/*Нейронная, дискретная сеть Хопфилда (Литтла).Автоассоциативная память - распознаём вектор и сапоставляем его с самим собой.
  (Сеть Хопфилда является однослойной).Синхронный режим работы*/

// Длина вектора
#define num_neuron 4
#define num_neuron1 3

// Правильные вектора
int8_t correct_vector_x[4][4] = {
  { 1, -1, 1, -1 },  //+ 1010
  { -1, 1, -1, 1 },  //+ 0101
  { 1, 1, 1, -1 },   //+ 1110
  { -1, -1, 1, -1 }  // 0010
};

int8_t correct_vector_y[4][3] = {
  { -1, -1, 1 },  //+ 001
  { -1, 1, -1 },  //+ 010
  { -1, 1, 1 },   //+ 011
  { 1, -1, -1 }   //+ 100
};

// Искаженный вектор
int8_t distorted_vector[] = { 1, -1, -1, -1 };  //+ 1000

//Возвращяющий вектор
int8_t back_vector[] = { -1, -1, 1};

// Весовая матрица (Запоминание образца сетью) (W = x^t*x)
int8_t weight_matrix[4][num_neuron1][num_neuron];
//int8_t weight_matrix_y[4][num_neuron1];

// Массив комбинированных вводов нейронов
int8_t Combined_input[num_neuron1];

int8_t NewMatrix[num_neuron1];

//CommonMatrix
int8_t CommonMatrix[num_neuron1][num_neuron];

//Massiv
int8_t Summa_1[num_neuron];
int8_t Summa_2[num_neuron];
int8_t Summa_3[num_neuron];
int8_t Summa_4[num_neuron];

// Массив активностей нейронов
int8_t element_activity[num_neuron1];

void setup() {
  Serial.begin(115200);
  // Обнуляем комбинированные вводы нейронов
  for (int8_t i = 0; i < num_neuron1; i++) {
    Combined_input[i] = 0;
  }

  // Определяем весовую матрицу по формуле W = x^t*x
  for (int8_t j = 0; j < num_neuron1; j++) {
    for (int8_t i = 0; i < num_neuron; i++) {
      weight_matrix[1][j][i] = correct_vector_y[1][j] * correct_vector_x[1][i];
      weight_matrix[2][j][i] = correct_vector_y[2][j] * correct_vector_x[2][i];
      weight_matrix[3][j][i] = correct_vector_y[3][j] * correct_vector_x[3][i];
      weight_matrix[0][j][i] = correct_vector_y[0][j] * correct_vector_x[0][i];
      //      Serial.println(weight_matrix[1][j][i]);
      //      Serial.println(weight_matrix[2][j][i]);
      //      Serial.println(weight_matrix[3][j][i]);
      //      Serial.println(weight_matrix[4][j][i]);
    }
  }



  for (int8_t j = 0; j < num_neuron; j++) {
    for (int8_t i = 0; i < num_neuron1; i++) {
      CommonMatrix[i][j] = weight_matrix[0][i][j] + weight_matrix[1][i][j] + weight_matrix[2][i][j] + weight_matrix[3][i][j];
    }
  }
}
void loop() {


  // Обнуляем комбинированные вводы нейронов
  for (uint8_t i = 0; i < num_neuron1; i++) {
    Combined_input[i] = 0;
  }


  //Получаем новую матрицу умножим Коммон на испорченный
  for (uint8_t i = 0; i < num_neuron1; i++) {
    for (uint8_t j = 0; j < num_neuron; j++) {
      NewMatrix[i] += (CommonMatrix[i][j] * distorted_vector[j]);
    }
  }


  // Активность нейронов
  for (uint8_t i = 0; i < num_neuron1; i++) {
    element_activity[i] = Element_Activity(NewMatrix[i]);
  }

  // Перезаписываем искаженный вектор на новый
  for (uint8_t i = 0; i < num_neuron1; i++) {
//    distorted_vector[i] = element_activity[i];
    Serial.println(NewMatrix[i]);
  }
  
  // Обнуляем комбинированные вводы нейронов
  for (uint8_t i = 0; i < num_neuron1; i++) {
    NewMatrix[i] = 0;
  }

  for (int i = 0; i < num_neuron1; i++) {
    if (element_activity[i] == 1)
      Serial.print("• ");
    if (element_activity[i] == -1)
      Serial.print("o ");
  }
  Serial.println();
  Serial.println("-----------------------------------------------------");

  delay(2000);
}


int8_t Element_Activity(int8_t val) {
  int8_t i;
  if (val > 0 ) {
    i = 1;
  }
  if (val <= 0) {
    i = -1;
  }
  return i;
}