
  #ifndef SPI_H_
  #define SPI_H_

  void spi_masterInit(void);
  void spi_write( unsigned char data );
  char spi_writeRead( unsigned char data );
  void spi_slaveSelect(unsigned char chipNumber);
  void spi_slaveDeSelect(unsigned char chipNumber);
   void displayDriverInit();
   void spi_writeWord ( unsigned char adress, unsigned char data );
    void display_nummer(int data);
  #endif