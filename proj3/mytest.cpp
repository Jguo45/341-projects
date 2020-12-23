#include "pqueue.h"
#include "iomanip"
using namespace std;

const string FAIL_STATEMENT = "*******TEST FAILED";
const string PASS_STATEMENT = "       TEST PASSED";

int priFn1(const Patient &patient);
int priFn2(const Patient &patient);

int main() {
  PQueue queue1(priFn1);

  Patient sam("Sam", 1, 37, 79,  36, 133, 75);
  Patient liz("Liz", 5, 37, 98, 26,  70, 100);
  Patient nick("Nick", 2, 37, 85, 34, 125, 85);
  Patient eva("Eva", 4, 37, 95,  22, 115, 95);
  Patient john("John", 3, 39, 91, 27, 115, 110);
  Patient mia("Mia", 3,  33, 93, 28, 118, 98);

  queue1.insertPatient(nick);
  queue1.insertPatient(liz);
  queue1.insertPatient(sam);
  queue1.insertPatient(eva);

  {
    PQueue queue2(queue1);

    cout << "Queue1: " << queue1.dump() << endl;
    cout << "Queue2: " << queue2.dump() << endl;

    if (queue1. != queue2) cout << FAIL_STATEMENT << " copy constructor" << endl;
  }

  

  // PQueue queue1(priFn1);
  // PQueue queue2(priFn2);

  // Patient sam("Sam", 1, 37, 79,  36, 133, 75);
  // Patient liz("Liz", 5, 37, 98, 26,  70, 100);
  // Patient nick("Nick", 2, 37, 85, 34, 125, 85);
  // Patient eva("Eva", 4, 37, 95,  22, 115, 95);

  // Patient john("John", 3, 39, 91, 27, 115, 110);
  // Patient mia("Mia", 3,  33, 93, 28, 118, 98);

  // queue1.insertPatient(nick);
  // queue1.insertPatient(sam);
  // queue1.insertPatient(liz);
  // queue1.insertPatient(eva);

  // cout << "before" << endl;
  // queue1.dump();
  // queue1 = queue2;
  // cout << "after" << endl;
  // queue1.dump();

  // queue2.insertPatient(john);
  // queue2.dump();
  // queue2.insertPatient(mia);
  // queue2.dump();

  // cout << "Queue1: " << endl;
  // queue1.dump();
  // cout << "\nQueue2: " << endl;
  // queue2.dump();
  // queue1.mergeWithQueue(queue2);
  // cout << "\nMerge: " << endl;
  // queue1.dump();
  // cout << "Size: " << queue1.numPatients() << endl;
  // queue1.printPatientQueue();

  // queue1.setPriorityFn(priFn2);
  // queue1.dump();
  // queue1.printPatientQueue();
  // cout << "Size: " << queue1.numPatients() << endl;

  // cout << endl;
}

int priFn2(const Patient&patient) {
  //priority only based on triage
  //traige is set by a health care professional
  return patient.getTriage();
}

int priFn1(const Patient&patient) {
  int pri = 5;
  if ((patient.getOxygen()<80 && (patient.getRR() > 35 || patient.getRR() < 8)) ||
      (patient.getHR() > 130 && patient.getBP() < 80))
      pri = 1;
  else if (((patient.getOxygen() >= 80 && patient.getOxygen() <= 89) && 
      (patient.getRR() >= 31 && patient.getRR() <= 35)) ||
      (patient.getTemperature() >= 40 || patient.getTemperature() <= 32))
      pri = 2;
  else if ((patient.getOxygen() >= 90 && patient.getOxygen() <= 94) && 
      (patient.getRR() >= 26 && patient.getRR() <= 30))
      pri = 3; 
  else if ((patient.getOxygen() >= 95 && patient.getOxygen() <= 97) && 
      (patient.getRR() >= 21 && patient.getRR() <= 25))
      pri = 4;
  else
      pri = 5;
  return pri;
}

void time(PQueue p, PQueue t) {
  clock_t start, end;
  start = clock();
  for (int i = 0; i <= 1000000; i++) {
    // p.insertPatient(Patient("test name", rand() % 5 + 1, rand() % 12 + 30, rand() % 31 + 70, rand() % 35 + 5, rand() % 105 + 35, rand() % 90 + 70));
    p.insertPatient(Patient("test name", 3, 37, 100, 30, 100, 90));
    // p.mergeWithQueue(t);
  }

  end = clock();

  double taken = double(end - start) / double(CLOCKS_PER_SEC);

  cout << "Time taken: " << fixed << taken << setprecision(5);
  cout << " sec" << endl;
}