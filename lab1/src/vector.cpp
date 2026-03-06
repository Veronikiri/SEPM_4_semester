bool init(subvector *qv) {
    qv->mas = nullptr;
    qv->top = 0;
    qv->capacity = 0;
    return true;
}

bool push_back(subvector *qv, int d) {
    if (qv->top >= qv->capacity) {
        unsigned int new_capacity = (qv->capacity == 0) ? 1 : qv->capacity * 2;
        int *new_mas = new int[new_capacity];
        if (new_mas == nullptr) {
            return false;
        }
        for (unsigned int i = 0; i < qv->top; ++i) {
            new_mas[i] = qv->mas[i];
        }
        if (qv->mas != nullptr) {
            delete[] qv->mas;
        }
        qv->mas = new_mas;
        qv->capacity = new_capacity;
    }
    qv->mas[qv->top] = d;
    qv->top++;
    return true;
}

int pop_back(subvector *qv) {
    if (qv->top == 0) {
        return 0;
    }
    qv->top--;
    return qv->mas[qv->top];
}

bool resize(subvector *qv, unsigned int new_capacity) {
    if (new_capacity < qv->top) {
        qv->top = new_capacity;
    }
    if (new_capacity == qv->capacity) {
        return true;
    }
    int *new_mas = new int[new_capacity];
    if (new_mas == nullptr) {
        return false;
    }
    for (unsigned int i = 0; i < qv->top; ++i) {
        new_mas[i] = qv->mas[i];
    }
    if (qv->mas != nullptr) {
        delete[] qv->mas;
    }
    qv->mas = new_mas;
    qv->capacity = new_capacity;
    return true;
}

void shrink_to_fit(subvector *qv) {
    if (qv->top == qv->capacity || qv->capacity == 0) {
        return;
    }
    if (qv->top == 0) {
        if (qv->mas != nullptr) {
            delete[] qv->mas;
        }
        qv->mas = nullptr;
        qv->capacity = 0;
        return;
    }
    int *new_mas = new int[qv->top];
    if (new_mas == nullptr) {
        return;
    }
    for (unsigned int i = 0; i < qv->top; ++i) {
        new_mas[i] = qv->mas[i];
    }
    if (qv->mas != nullptr) {
        delete[] qv->mas;
    }
    qv->mas = new_mas;
    qv->capacity = qv->top;
}

void clear(subvector *qv) {
    qv->top = 0;
}

void destructor(subvector *qv) {
    if (qv->mas != nullptr) {
        delete[] qv->mas;
    }
    qv->mas = nullptr;
    qv->top = 0;
    qv->capacity = 0;
}
