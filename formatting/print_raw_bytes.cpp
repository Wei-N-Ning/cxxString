//
// Created by weining on 6/6/20.
//

// source:
// https://stackoverflow.com/questions/10599068/how-do-i-print-bytes-as-hexadecimal

void print_bytes()
{
    std::byte stackBuf[ 128 ];

    using namespace std;
    cout << hex << setfill( '0' );  // needs to be set only once
    auto *ptr = reinterpret_cast< unsigned char * >( stackBuf );
    for ( int i = 0; i < 64; i++, ptr++ )
    {
        if ( i && i % 32 == 0 )
        {
            cout << endl;
        }
        cout << setw( 2 ) << static_cast< unsigned >( *ptr ) << " ";
    }
    cout << endl;
}