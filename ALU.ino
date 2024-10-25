int EstadoA = 0;
int EstadoB = 0;
int Operacion = 0;

void setup() {
  pinMode(2, INPUT);  // Botón A
  pinMode(3, INPUT);  // Botón B
  pinMode(4, INPUT);  // DIP switch bit 0
  pinMode(5, INPUT);  // DIP switch bit 1
  pinMode(6, INPUT);  // DIP switch bit 2
  pinMode(7, INPUT);  // DIP switch bit 3
  pinMode(12, OUTPUT); // LED Resultado
  pinMode(13, OUTPUT); // LED Acarreo
  pinMode(8, OUTPUT);  // LED Negativo
  pinMode(9, OUTPUT);  // LED Infinito
  pinMode(11, OUTPUT); // LED Indeterminación
  pinMode(10, OUTPUT); // LED Error

  Serial.begin(9600); // Inicializar comunicación serial
}

void loop() {
  EstadoA = digitalRead(2);
  EstadoB = digitalRead(3);
  Operacion = (digitalRead(4) << 0) | (digitalRead(5) << 1) | (digitalRead(6) << 2) | (digitalRead(7) << 3);

  // Reset LEDs
  digitalWrite(12, LOW);
  digitalWrite(13, LOW);
  digitalWrite(8, LOW);
  digitalWrite(9, LOW);
  digitalWrite(11, LOW);
  digitalWrite(10, LOW);

  switch (Operacion) {
    case 0: // No operation
      break;
    case 1: // Suma
      if (EstadoA ^ EstadoB) {
        digitalWrite(12, HIGH);
      }
      if (EstadoA && EstadoB) {
        digitalWrite(13, HIGH);
      }
      break;
    case 2: // Resta
      if (EstadoA && !EstadoB) {
        digitalWrite(12, HIGH);
      }
      if (!EstadoA && EstadoB) {
        digitalWrite(12, HIGH);
        digitalWrite(8, HIGH);

      }
      break;
    case 3: // Multiplicación
      if (EstadoA && EstadoB) {
        digitalWrite(12, HIGH);
      }
      break;
    case 4: // División
	digitalWrite(11, HIGH);

      if (EstadoA && EstadoB) {
        digitalWrite(12, HIGH);
	digitalWrite(11, LOW);

       
      } else if (EstadoA && !EstadoB) {
        digitalWrite(9, HIGH); 
	digitalWrite(11, LOW);
        
      }else if (!EstadoA && EstadoB) {
        
        
      }
      break;
    case 5: // AND
      if (EstadoA && EstadoB) {
        digitalWrite(12, HIGH);
        
      }
      break;
    case 6: // OR
      if (EstadoA ^ EstadoB) {
        digitalWrite(12, HIGH);
        Serial.println("Operación OR realizada: Resultado = 1");
      }
      break;
    

      break;
    case 7: // NOT 
      if (!EstadoA) {
        digitalWrite(12, HIGH);
      }
      break;
    

	case 8: // XOR
      if (EstadoA && EstadoB) {
       
      } else if (!EstadoA && EstadoB){
	digitalWrite(12, HIGH);

      } else if (EstadoA && !EstadoB){
	digitalWrite(12, HIGH);
      } else if (!EstadoA && !EstadoB){
	
      }
	break;

	case 9: //XNOR
	if (EstadoA && EstadoB) {
       digitalWrite(12,HIGH);
      } else if (!EstadoA && !EstadoB){
	digitalWrite(12, HIGH);}
	break;

	case 10: //NAND

	if (!EstadoA && !EstadoB){
	    digitalWrite(12,HIGH);

	} else if (EstadoA && !EstadoB){
	    digitalWrite(12,HIGH);
	} else if (!EstadoA && EstadoB){
	    digitalWrite(12,HIGH);
	} else if (EstadoA && EstadoB){}
	break;

	case 11: //NOR
	if (!EstadoA && !EstadoB){
	    digitalWrite(12,HIGH);

	break;
	
    default:
      digitalWrite(10, HIGH); // Indeterminación para operaciones no definidas
      break;
  }

}
