/*
银行业务模拟
客户业务分为两种：
第一种是申请从银行得到一笔资金，即取款或借款；
第二种是向银行投入一笔资金，即存款或还款。

银行有两个服务窗口，相应地有两个队列。客户到达银行后先排第一个队，处理每个客户业务时，如果属于第一种，且申请额超出银行现存资金总额而得不到满足，则立刻排入第二个队等候直至满足时才离开银行;否则业务处理完后立刻离开银行,每接待完一个第二种业务的客户，则顺序检查和处理(如果可能)第二个队列中的客户，对能满足的申请者予以满足,不能满足者重新排到第二个队列的队尾。注意，在此检查过程中，一旦银行资金总额少于或等于刚才第一个队列中最后一个客户(第二种业务)被接待之前的数额，或者本次已将第二个队列检查或处理了一遍，就停止检查(因为此时已不可能还有能满足者)转而继续接待第一个队列的客户。任何时刻都只开一个窗口。假设检查不需要时间，营业时间结束时所有客户立即离开银行。

写一个上述银行业务的事件驱动模拟系统，通过模拟方法求出客户在银行内逗留的平均时间。
*/


#include <cstdio>

struct Event
{
    int id;//与事件相关的客户的编号
    int type;//事件类型
    int time;//事件发生时间
    Event *next;
};

struct Customer
{
    int id;//客户的编号
    Customer *next;
};

struct Record
{
    int money;//业务相关的钱数
    int arrive;//到达时间
    int service;//开始接受服务时间
};


class Queue_Event
{
public:
    Queue_Event()
    {
        head = NULL;
        tail = NULL;
    }

    int isEmpty()
    {
        if (head == NULL) return 1;
        else return 0;
    }

    void deQueue()
    {
        Event *p = head;
        if (head == NULL) return;
        if (head == tail) head = NULL;
        else head = head->next;
        delete p;
    }

    void enQueue(int id,int type,int time)
    {
        Event *t = new Event;
        t->id = id;
        t->time = time;
        t->type = type;
        if (head == NULL)
        {
            head = t;
            tail = t;
            tail->next = NULL;
        }
        else
        {
            tail->next = t;
            tail = t;
            tail->next = NULL;
        }
    }

    void insertByTime(int id,int type, int time)
    {
        Event *t = new Event;
        t->id = id;
        t->time = time;
        t->type = type;
        if (head == NULL)
        {
            head = t;
            tail = t;
            tail->next = NULL;
            return;
        }
        if (head->time >= t->time)
        {
            t->next = head;
            head = t;
            return;
        }
        Event *q = head, *r = head->next;
        while (r != NULL && r->time < t->time)
        {
            q = q->next;
            r = r->next;
        }
        q->next = t;
        t->next = r;
        if (r == NULL)
        {
            tail = t;
        }
    }

    void insertHead(int id, int type, int time)
    {
        Event *t = new Event;
        t->id = id;
        t->time = time;
        t->type = type;
        if (head == NULL)
        {
            head = t;
            tail = t;
            tail->next = NULL;
            return;
        }
        t->next = head;
        head = t;
    }

    int typeOfHead()
    {
        if (head == NULL) return -1;
        else return head->type;
    }

    int timeOfHead()
    {
        if (head == NULL) return -1;
        else return head->time;
    }

    int idOfHead()
    {
        if (head == NULL) return -1;
        else return head->id;
    }

private:
    Event *head;
    Event *tail;
};

class Queue_Customer
{
public:
    Queue_Customer()
    {
        head = NULL;
        tail = NULL;
    }

    int isEmpty()
    {
        if (head == NULL) return 1;
        else return 0;
    }

    void deQueue()
    {
        Customer *p = head;
        if (head == NULL) return;
        if (head == tail) head = NULL;
        else head = head->next;
        delete p;
    }

    void enQueue(int id)
    {
        Customer *p = new Customer;
        p->id = id;
        if (head == NULL)
        {
            head = p;
            tail = p;
        }
        else
        {
            tail->next = p;
            tail = p;
        }
    }

    int idOfHead()
    {
        if (head == NULL) return -1;
        else return head->id;
    }

private:
    Customer *head;
    Customer *tail;
};




int main()
{
    int N;//今天来银行的总人数
    int total;//银行今天开始营业时拥有的款额
    int close_time;//今天银行的营业时长
    int average_time;//每个客户的交易时长
    Record record[10000];
    int i,TwoIsBusy = 0,id,type,money,time,IdHead,sum=0;

    Queue_Event EventQueue;//事件队列
    Queue_Customer QueueOne;//银行大厅中的第一队列
    Queue_Customer QueueTwo;//银行大厅中的第二队列
    
    scanf("%d %d %d %d", &N, &total, &close_time, &average_time);
    for (i = 1; i <= N; i++)
    {
        scanf("%d %d", &money, &time);
        EventQueue.enQueue(i,money >= 0 ? 0 : 3, time);
        record[i].money = money;
        record[i].arrive = time;
        record[i].service = -1;
    }

    while (!EventQueue.isEmpty())
    {
        type = EventQueue.typeOfHead();
        time = EventQueue.timeOfHead();
        id = EventQueue.idOfHead();
        EventQueue.deQueue();
        if (time > close_time)
        {
            break;
        }
        switch (type)
        {
            case 0://第id号客户在time时间来到银行，想存钱
            {
                QueueOne.enQueue(id);
                if (!TwoIsBusy && id == QueueOne.idOfHead())
                    EventQueue.insertHead(id, 1, time);//一号柜台立刻开始服务
                break;
            }

            case 1://一号柜台队首的客户（id号客户）在time时间开始进行存钱业务
            {
                record[id].service = time;//记录他的等待时间
                EventQueue.insertByTime(id, 2, time + average_time);//设定好他的离开事件
                break;
            }

            case 2://一号柜台队首的客户（id号客户）在time时间完成了存钱业务
            {
                QueueOne.deQueue();
                total = total + record[id].money;

                if (QueueTwo.isEmpty())
                {
                    if (!QueueOne.isEmpty())
                    {
                        EventQueue.insertHead(QueueOne.idOfHead(), record[QueueOne.idOfHead()].money >= 0 ? 1 : 4, time);//一号柜台立刻开始服务
                    }
                }
                else
                {
                    IdHead = QueueTwo.idOfHead();//记录第二队列目前的队首客户的id
                    if (total + record[IdHead].money >= 0)
                    {
                        EventQueue.insertHead(IdHead, 6, time);
                    }
                    else
                    {
                        QueueTwo.enQueue(IdHead);
                        QueueTwo.deQueue();
                        id = QueueTwo.idOfHead();
                        while (id != IdHead)
                        {
                            if (total + record[id].money >= 0)
                            {
                                EventQueue.insertHead(id, 6, time);
                                goto case_2_bre;
                            }
                            QueueTwo.enQueue(id);
                            QueueTwo.deQueue();
                            id = QueueTwo.idOfHead();
                        }
                        if (!QueueOne.isEmpty())
                        {
                            EventQueue.insertHead(QueueOne.idOfHead(), record[QueueOne.idOfHead()].money >= 0 ? 1 : 4, time);//一号柜台立刻开始服务
                        }
                    }
                }
                case_2_bre: break;
            }

            case 3://第id号客户在time时间来到银行，想取钱
            {
                QueueOne.enQueue(id);
                if (!TwoIsBusy && id == QueueOne.idOfHead())
                {
                    if (total + record[id].money >= 0)
                    {
                        EventQueue.insertHead(id, 4, time);
                    }
                    else
                    {
                        QueueTwo.enQueue(id);
                        QueueOne.deQueue();
                        if (!QueueOne.isEmpty())
                        {
                            EventQueue.insertHead(QueueOne.idOfHead(), record[QueueOne.idOfHead()].money >= 0 ? 1 : 4, time);//一号柜台立刻开始服务
                        }
                    }
                }
                break;
            }

            

            case 4://一号柜台队首的客户（id号客户）在time时间开始进行取钱业务
            {
                if (total + record[id].money >= 0)
                {
                    record[id].service = time;//记录他的等待时间
                    EventQueue.insertByTime(id, 5, time + average_time);//设定好他的离开事件
                }
                else
                {
                    QueueTwo.enQueue(id);
                    QueueOne.deQueue();
                    if (!QueueOne.isEmpty())
                    {
                        EventQueue.insertHead(QueueOne.idOfHead(), record[QueueOne.idOfHead()].money >= 0 ? 1 : 4, time);//一号柜台立刻开始服务
                    }
                }
                break;
            }

            

            case 5://一号柜台队首的客户（id号客户）在time时间完成了取钱业务
            {
                QueueOne.deQueue();
                total = total + record[id].money;
                if (!QueueOne.isEmpty())
                {
                    EventQueue.insertHead(QueueOne.idOfHead(), record[QueueOne.idOfHead()].money >= 0 ? 1 : 4, time);//一号柜台立刻开始服务
                }
                break;
            }

            case 6://二号柜台队首的客户（id号客户）在time时间开始进行取钱业务
            {
                TwoIsBusy = 1;
                record[id].service = time;//记录他的等待时间
                EventQueue.insertByTime(id, 7, time + average_time);//设定好他的离开事件
                break;
            }

            case 7://二号柜台队首的客户（id号客户）在time时间完成了取钱业务
            {
                TwoIsBusy = 0;
                total = total + record[id].money;
                QueueTwo.deQueue();

                if (QueueTwo.isEmpty())
                {
                    if (!QueueOne.isEmpty())
                    {
                        EventQueue.insertHead(QueueOne.idOfHead(), record[QueueOne.idOfHead()].money >= 0 ? 1 : 4, time);//一号柜台立刻开始服务
                    }
                }
                else
                {
                    IdHead = QueueTwo.idOfHead();//记录第二队列目前的队首客户的id
                    if (total + record[IdHead].money >= 0)
                    {
                        EventQueue.insertHead(IdHead, 6, time);
                    }
                    else
                    {
                        QueueTwo.enQueue(IdHead);
                        QueueTwo.deQueue();
                        id = QueueTwo.idOfHead();
                        while (id != IdHead)
                        {
                            if (total + record[id].money >= 0)
                            {
                                EventQueue.insertHead(IdHead, 6, time);
                                goto case_7_bre;
                            }
                            QueueTwo.enQueue(id);
                            QueueTwo.deQueue();
                            id = QueueTwo.idOfHead();
                        }
                        if (!QueueOne.isEmpty())
                        {
                            EventQueue.insertHead(QueueOne.idOfHead(), record[QueueOne.idOfHead()].money >= 0 ? 1 : 4, time);//一号柜台立刻开始服务
                        }
                    }
                }
                case_7_bre: break;
            }
        }
    }
    for (i = 1; i <= N; i++)
    {
        if (record[i].service == -1)
        {
            record[i].service = close_time;
        }
        printf("%d\n", record[i].service - record[i].arrive);
        sum += record[i].service - record[i].arrive;
    }
    printf("%d\n", sum / N);
    return 0;
}
