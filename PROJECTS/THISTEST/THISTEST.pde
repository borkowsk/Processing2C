/// Test dla problemu z użyciem "this" jako parametru funkcji oczekujących Processing::ptr<...>
/// To powoduje GPF bo tworzy się nowy _shared_ptr<> nie powiązany z tym trzymającym obiekt! 
