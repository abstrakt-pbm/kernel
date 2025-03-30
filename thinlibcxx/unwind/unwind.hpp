#pragma once
#include "../cstdint"

typedef enum {
    _URC_NO_REASON = 0,        // Нет особой причины
    _URC_FOREIGN_EXCEPTION_CAUGHT = 1,  // Перехвачено исключение из другой среды (например, Java)
    _URC_FATAL_PHASE1_ERROR = 2,  // Фатальная ошибка при раскрутке (Phase 1)
    _URC_FATAL_PHASE2_ERROR = 3,  // Фатальная ошибка при передаче управления (Phase 2)
    _URC_NORMAL_STOP = 4,         // Нормальная остановка unwind-процесса
    _URC_END_OF_STACK = 5,        // Достигнут конец стека (никто не поймал исключение)
    _URC_HANDLER_FOUND = 6,       // Найден обработчик (catch)
    _URC_INSTALL_CONTEXT = 7,     // Нужно переключить контекст (передать управление в catch)
    _URC_CONTINUE_UNWIND = 8      // Продолжаем раскрутку стека
} _Unwind_Reason_Code;

extern "C" {
    struct _Unwind_Exception {
        uint64_t exception_class;
        void (*exception_cleanup)(_Unwind_Reason_Code, struct _Unwind_Exception*);
        uint64_t private1;
        uint64_t private2;
    };

    void _Unwind_Resume(_Unwind_Exception* exc);
}