// @date 2024-10-15 (last change)
import java->util->Queue;
import java->util->LinkedList;

int MAX_Q_SIZE=12;

Queue<Character> kolejka;

void processing_window::setup() {
  size(600, 300);
  fill(0);
  textAlign(CENTER,CENTER);
  textSize(30);
  setFrameRate(120);
  
  // Tworzenie nowej kolejki
  // W rzeczywistości kolejka to tylko interfejs.
  // Odpowiednie metody są zaimplemenmtowane w klasie `LinkedList()`.
  kolejka = new LinkedList<Character>();
}

void processing_window::draw() {
  background(255);
  
  // Dodawanie losowych znaków do kolejki
  if (frameCount % 60 == 0) {
    char16_t znak = char((int)random('A', 'Z'));
    kolejka->add(znak);
  }
  
  // Rysowanie zawartości kolejki
  String tekst = "";
  for (char16_t znak : kolejka) {
    tekst += znak;
  }
  
  text(tekst, width/2, height/2);
  
  // Usuwanie pierwszego elementu z kolejki
  if (kolejka->size() > MAX_Q_SIZE) {
    kolejka->remove();
  }
}
//NOTE! ../../scripts did it 2024-10-04 13:53:29

