
// When customers arrive they join the single queue. When they get to the end of the queue,
// they pick the next free counter to go place their order.


#include <stdlib.h>
#include <time.h>

#include <iostream>

using namespace std;

class Customer {
 public:
  int inTime;
  // int orderWaitRemaining;
  Customer *next;

  Customer() {
    inTime = -1;
    // orderWaitRemaining = -1;
    next = NULL;
  }
};

class Queue {
 public:
  Customer *head;

  Queue() { head = NULL; }

  void enqueue(int inTime) {
    Customer *temp = new Customer;
    temp->inTime = inTime;
    if (head == NULL) {
      head = temp;
    } else {
      temp->next = head;
      head = temp;
    }
  }

  bool queueEmpty() {
    if (head == NULL) {
      return true;
    } else {
      return false;
    }
  }

  int dequeue() {
    int startTime;
    if (head == NULL) {
      // cout << "Queue empty, nothing to remove\n";
      return -1;
    } else if (head->next == NULL) {
      startTime = head->inTime;
      delete head;
      head = NULL;
      return startTime;
    } else {
      Customer *chase, *follow;
      chase = follow = head;
      while (chase->next != NULL) {
        follow = chase;
        chase = chase->next;
      }
      follow->next = NULL;
      startTime = chase->inTime;
      delete chase;
      return startTime;
    }
  }
};

int TIME = 0;

bool isPeakHours(){
  if ((TIME >= 0 && TIME < 120) || (TIME >= 210 && TIME < 330) ||
      (TIME >= 570 && TIME < 720)) {
    return true;
  }else{
    return false;
  }
}

int main() {
  int generator;
  int queueHold = 0;
  int orderHold = 0;
  int orderHold2 = 0;
  double averageWaitTimeSum = 0;
  double averageServiceTimeSum = 0;
  double averageQueueLengthSum = 0;
  int numOfCust = 0;  // in order queue
  int bestWait = 0;
  int worstWait = 0;
  int bestService = 0;
  int worstService = 0;
  int startTime = 0;
  int startTime2 = 0;
  bool waitSet = false;
  bool waitSet2 = false;
  bool serviceSet = false;
  bool serviceSet2 = false;
  bool orderInProgress = false;
  bool orderInProgress2 = false;
  int totCust = 0;
  Queue orderQueue;
  srand(time(NULL));

  // Store hours, every minute of a day
  while (TIME < 1020) {
    // 1. should we add a new customore to the Q at this minute?
    if (TIME >= 0 && TIME < 120) {
      // 8:00am through 10:00am (Breakfast)
      generator = rand() % 100 + 1;
      if (generator <= 30) {
        orderQueue.enqueue(TIME);
        numOfCust++;
        totCust++;
      }
    } else if (TIME >= 120 && TIME < 210) {
      // 10:00am through 11:30am
      generator = rand() % 100 + 1;
      if (generator <= 10) {
        orderQueue.enqueue(TIME);
        numOfCust++;
        totCust++;
      }
    } else if (TIME >= 210 && TIME < 330) {
      // 11:30am through 1:30pm (Lunch)
      generator = rand() % 100 + 1;
      if (generator <= 40) {
        orderQueue.enqueue(TIME);
        numOfCust++;
        totCust++;
      }
    } else if (TIME >= 330 && TIME < 570) {
      // 1:30pm through 5:30pm
      generator = rand() % 100 + 1;
      if (generator <= 10) {
        orderQueue.enqueue(TIME);
        numOfCust++;
        totCust++;
      }
    } else if (TIME >= 570 && TIME < 720) {
      // 5:30pm through 8:00pm (Dinner)
      generator = rand() % 100 + 1;
      if (generator <= 25) {
        orderQueue.enqueue(TIME);
        numOfCust++;
        totCust++;
      }
    } else if (TIME >= 720 && TIME < 900) {
      // 8:00pm through 11:00pm
      generator = rand() % 100 + 1;
      if (generator <= 20) {
        orderQueue.enqueue(TIME);
        numOfCust++;
        totCust++;
      }
    } else if (TIME >= 900) {
      // 11:00pm through 1:00am
      generator = rand() % 100 + 1;
      if (generator <= 10) {
        orderQueue.enqueue(TIME);
        numOfCust++;
        totCust++;

      }
    }
    
      
    

    if (!orderQueue.queueEmpty() && orderHold == 0 && !orderInProgress) {
      startTime = orderQueue.dequeue();
      int waitTime = TIME - startTime;
      averageWaitTimeSum += waitTime;
      numOfCust--;
      orderInProgress = true;
      orderHold = rand() % 6 + 1;
      if (!waitSet){
        bestWait = waitTime;
        worstWait = waitTime;
        waitSet = true;
      }else{
        if(bestWait > waitTime){
          bestWait = waitTime;
        }else if(worstWait < waitTime){
          worstWait = waitTime;
        }
      }
    }else if(!orderQueue.queueEmpty() && orderHold == 0 && orderInProgress){
      int serviceTime = TIME - startTime;
      // cout << "Order picked Up, start time " << startTime << "\n";
      averageServiceTimeSum += serviceTime;
      if (!serviceSet) {
        bestService = serviceTime;
        worstService = serviceTime;
        serviceSet = true;
      } else {
        if (bestService > serviceTime) {
          bestService = serviceTime;
        } else if (worstService < serviceTime) {
          worstService = serviceTime;
        }
      }
      orderInProgress = false;
    }else if (!orderQueue.queueEmpty() && orderHold > 0) {
      orderHold--;
    }
    // only runs during peak hours, makes another position to wait for orders
    if (!orderQueue.queueEmpty() && orderHold2 == 0 && !orderInProgress2 && isPeakHours()) {
      startTime2 = orderQueue.dequeue();
      int waitTime2 = TIME - startTime2;
      averageWaitTimeSum += waitTime2;
      numOfCust--;
      orderInProgress2 = true;
      orderHold2 = rand() % 6 + 1;
      if (!waitSet2){
        bestWait = waitTime2;
        worstWait = waitTime2;
        waitSet2 = true;
      }else{
        if(bestWait > waitTime2){
          bestWait = waitTime2;
        }else if(worstWait < waitTime2){
          worstWait = waitTime2;
        }
      }
    }else if(!orderQueue.queueEmpty() && orderHold2 == 0 && orderInProgress2 && isPeakHours()){
      int serviceTime2 = TIME - startTime;
      // cout << "Order picked Up, start time " << startTime << "\n";
      averageServiceTimeSum += serviceTime2;
      if (!serviceSet2) {
        bestService = serviceTime2;
        worstService = serviceTime2;
        serviceSet2 = true;
      } else {
        if (bestService > serviceTime2) {
          bestService = serviceTime2;
        } else if (worstService < serviceTime2) {
          worstService = serviceTime2;
        }
      }
      orderInProgress2 = false;
    }else if (!orderQueue.queueEmpty() && orderHold2 > 0 && isPeakHours()) {
      orderHold2--;
    }

    averageQueueLengthSum += numOfCust;
    TIME++;


  }

  averageWaitTimeSum /= totCust;
  averageServiceTimeSum /= totCust;
  averageQueueLengthSum /= 1020;

  cout << "Average Wait time: " << averageWaitTimeSum << "\n";
  cout << "Average Service Time: " << averageServiceTimeSum << "\n";
  cout << "Average Queue Length: " << averageQueueLengthSum << "\n";
  cout << "Fastest Wait Time: " << bestWait << "\n";
  cout << "Longest Wait Time: " << worstWait << "\n";
  cout << "Fastest Service Time: " << bestService << "\n";
  cout << "Longest Service Time: " << worstService << "\n";
}
