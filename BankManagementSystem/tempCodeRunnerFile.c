struct Account acc;
    struct Customer cus;
    int res = findeAccount(&acc);
    if (!res)
        puts("Account cannot be found!");