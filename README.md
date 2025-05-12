# PROJECT LOADCELL FINAL

## KENAPA FINAL
<p>
Karena saya sudah memahami kodingan c dan cpp walaupun tidak penuh.
Di lain sisi pemahaman akan arsitektur pembuatan software juga mulai utuh.
Hanya saja masih butuh jam terbang untuk algoritma yang berjalan dengan manual.
Misalkan seperti perpindahan cursor di dalam display atau perubahan character pada cursor lcd juga.
Sedangkan untuk fungsi-fungsi utama lain sudah mulai beres.
Kodingan ini saya buat sendiri ditemani oleh AI dalam rangka asisten.
AI pada awalnya sebagai logika dasar dalam membuat project ini karena saya tidak tahu menahu tentang MCU.
Namun, akibat keterbatasan dari AI dan pemahaman saya yang sudah cukup baik, maka saya memutuskan logika utama dari saya.
AI membantu dalam rangka pencarian dan pengujian terhadap bug dan kesalahan-kesalahan minor.
AI juga mempercepat proses pemahaman dan penguasaan terhadap embedded system dan juga C dan CPP itu sendiri.
</p>

## Language
<p>
Secara umum bahasa utama adalah C sedangkan CPP adalah sebagai wrapper.
Wrapper berfungsi sebagai penghubung library external yang tidak bisa secara langsung digunakan oleh C.
Ujung-ujungnya .cpp tadi akan digunakan oleh C untuk mengelola proses di dalamnya.
</p>

## SERIAL
<p>
Serial adalah sesuatu yang aneh juga.
Semua hal untuk menampilan atau mengkomunikasikan data berawal dari serial.
Tampilan dengan lcd juga serial dan tampilan untuk debugging juga menggunakan serial.
Barangkali juga nanti ketika berkomunikasi dengan wireless juga serial.
</p>

## Koneksi
<ul>
    <li>Nanti akan menggunakan Bluetooth untuk komunikasi dengan android. (BLE)</li>
    <li>Menggunakan ESP-NOW untuk berkomunikasi wifi antar ESP</li>
</ul>

## Harware
<ul>
    <li>Menggunakan arduino nano untuk MCU utama</li>
    <li>HX711 menjadi input dari arduino</li>
    <li>LCD Display 16x2 juga dengan arduino</li>
    <li>Arduino akan berkomunikasi dengan ESP32 untuk pengiriman dan penerimaan data dari device lain.</li>
    <li>Sementara, device B jika sekarang yang saya lakukan adalah device A belum dibuat</li>
</ul>