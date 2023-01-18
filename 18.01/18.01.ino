//вроде как ассинхронная под 5 картинок

/*Нейронная, дискретная сеть Хопфилда (Литтла).Автоассоциативная память - распознаём вектор и сапоставляем его с самим собой.
  (Сеть Хопфилда является однослойной).Синхронный режим работы*/

// Длина вектора
#define num_neuron 4  
#define num_neuron1 3

// Правильные вектора
int8_t correct_vector_x[4][4] = {
  { 1, -1, 1, -1 },  //+
  { -1, 1, -1, 1 },  //+
  { 1, 1, 1, -1 },   //+
  { -1, -1, 1, -1 }  //
};

int8_t correct_vector_y[4][3] = {
  { -1, -1, 1 },  //+
  { -1, 1, -1 },  //+
  { -1, 1, 1 },   //+
  { 1, -1, -1 }   //+
};

// Искаженный вектор
int8_t distorted_vector[] = { 1, -1, -1, -1 };  //+

// Весовая матрица (Запоминание образца сетью) (W = x^t*x)
int8_t weight_matrix[4][num_neuron][num_neuron];
//int8_t weight_matrix_y[4][num_neuron1];

// Массив комбинированных вводов нейронов
int8_t Combined_input[num_neuron];

int8_t NewMatrix[num_neuron];

//CommonMatrix
int8_t CommonMatrix[num_neuron][num_neuron];

//Massiv
int8_t Summa_1[num_neuron];
int8_t Summa_2[num_neuron];
int8_t Summa_3[num_neuron];
int8_t Summa_4[num_neuron];

// Массив активностей нейронов
int8_t element_activity[num_neuron];

void setup() {
  Serial.begin(115200);
  // Обнуляем комбинированные вводы нейронов
  for (int8_t i = 0; i < num_neuron; i++) {
    Combined_input[i] = 0;
  }

  // Определяем весовую матрицу по формуле W = x^t*x

  for (int8_t j = 0; j < num_neuron; j++) {
    for (int8_t i = 0; i < num_neuron1; i++) {
      weight_matrix[1][j][i] = correct_vector_y[1][i] * correct_vector_x[1][j]; 
      weight_matrix[2][j][i] = correct_vector_y[2][i] * correct_vector_x[2][j]; 
      weight_matrix[3][j][i] = correct_vector_y[3][i] * correct_vector_x[3][j]; 
      weight_matrix[4][j][i] = correct_vector_y[4][i] * correct_vector_x[4][j]; 
    }
  }
  for (int8_t n = 0; n <= 4; n++)
    for (int8_t j = 0; j < num_neuron; j++) {
      for (int8_t i = 0; i < num_neuron1; i++) {
        CommonMatrix[j][i] = weight_matrix[1][j][i] + weight_matrix[2][j][i] + weight_matrix[3][j][i] + weight_matrix[4][j][i];
        Serial.println(CommonMatrix);
      }
    }

  // Обнуляем диагональные элементы матрицы
  for (int8_t i = 0; i < num_neuron; i++) {
    CommonMatrix[i][i] = 0;
  }
}

void loop() {



  // Обнуляем комбинированные вводы нейронов
  for (uint8_t i = 0; i < num_neuron; i++) {
    Combined_input[i] = 0;
  }


  //Получаем новую матрицу умножим Коммон на испорченный
  for (uint8_t i = 0; i < num_neuron; i++) {
    for (uint8_t j = 0; j < num_neuron; j++) {
      NewMatrix[i] += (CommonMatrix[i][j] * distorted_vector[j]);
      Serial.println(NewMatrix);
    }
  }


  // Активность нейронов
  for (uint8_t i = 0; i < num_neuron; i++) {
    element_activity[i] = Element_Activity(NewMatrix[i]);
  }

  // Перезаписываем искаженный вектор на новый
  for (uint8_t i = 0; i < num_neuron; i++) {
    distorted_vector[i] = element_activity[i];
  }

  //  count--;
  //  if ( count < 0) {
  //    count = numNeuron - 1;
  //  }

  //  int sum = 0;
  //  for ( int i = 0; i < 2; i++ ) {
  //    for ( int j = (0 + sum); j < (2 + sum); j++ ) {
  //
  //      if (  distorted_vector[j] == 1 )
  //        Serial.print("• ");
  //      if ( distorted_vector[j] == -1)
  //        Serial.print("o ");
  //    }
  //    sum += 2;
  //    Serial.println();
  //  }

  for (int i = 0; i < 3; i++) {
    if (distorted_vector[i] == 1)
      Serial.print("• ");
    if (distorted_vector[i] == -1)
      Serial.print("o ");
  }
  Serial.println();
  Serial.println("-----------------------------------------------------");

  delay(2000);
}



int8_t Element_Activity(int8_t val) {
  int8_t i;
  if (val > 0 || val == 0) {
    i = 1;
  }
  if (val < 0) {
    i = -1;
  }
  return i;
}