This is not a read me! As stated in README however, this is an educational project for learning the ropes of embedded C. SO PLEASE DON'T USE THIS FOR SOMETHING OTHER THAN A HOBBY PROJECT! 

With that said, this file is purely used to log my design choices and lessons learnt as I go. The logs in this file only go as far back as the implementation of enum error types.

27-11-2025:

    Reviewing my progress from main made me realise I needed to do more to leave behind the
    object orientated paradigm I've been using for so long. Where main looked like this:

        pico_prov_init()

        if (pico_prov_has_credentials() || pico_prov_btn_pressed())

            ...

    I realised this is a terrible way to do things as it forces not only a gpio button
    implementation on the programmer, but an unnecessary function for checking data that
    the programmer can't even access.

    Hence, to adhere to the true nature of C, I'm refactoring the code to pass a credentials
    struct by reference, and assigning values to the struct within the init func.

    By doing this, the programmer will have full access/say of the data extracted from the 
    flash file system. From here, the programmer can choose to use other methods for provisioning
    and so on...

    

