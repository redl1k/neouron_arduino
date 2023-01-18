//Эталонное изображение
int referenceImage[4] = {1, -1, 1, -1};

//Искаженное изображение
int distortedImage[4] = {1, -1, 1, 1};

//Общая матрица
int matrix[4][4];

//Финальный вектор
int finalVector[4];


void setup() {
  Serial.begin(9600);
  //Умножаем оригинальный вектор на тр.вектор
  for ( int i = 0; i < 4; i++) { 
    for ( int j = 0; j < 4; j++){
      matrix[i][j] = referenceImage[i] * referenceImage[j];
      Serial.print(matrix[i][j]);
      Serial.print()
    }
    Serial.println();   
  }
}

void loop() {
  //Умножаем общую матрицу на испорченный образец
  for ( int i = 0; i < 4; i++ ){  
    for (int j = 0; j < 4; j++){
      finalVector[0] += (matrix[0][j] * distortedImage[j]);
    }
    Serial.println(finalVector[i]);
    Serial.println('   ');
  }
  while(1);
}

int signFunction(int neuron) {
  if (neuron >= 0)
    return 1;
  if (neuron < 0)
    return -1;
}

