/*******************************************************************************
Name:               Roy Yablonka
Group:              RD70
WS:                 CPP2C
Last Updated:       10/11/2019 10:12
*******************************************************************************/
#define MAX_FUNC(A, B) (A > B ? A : B)

#include <stdio.h>  /*printf*/
#include <stddef.h> /*size_t*/
#include <stdlib.h> /*malloc*/

/*******************************************************************************
                        STATIC VARS DECLARATIONS
*******************************************************************************/
int public_transport_g_count = 0;

/*******************************************************************************
                        STRUCT TYPEDEFS DECLARATIONS
*******************************************************************************/
typedef struct PublicTransport_s PublicTransport_t;
typedef struct PublicTransportVTable_s PublicTransportVTable_t;
typedef struct Minibus_s Minibus_t;
typedef struct MinibusVTable_s MinibusVTable_t;
typedef struct Taxi_s Taxi_t;
typedef struct TaxiVTable_s TaxiVTable_t;
typedef struct SpecialTaxi_s SpecialTaxi_t;
typedef struct SpecialTaxiVTable_s SpecialTaxiVTable_t;

/*******************************************************************************
                        FUNCTION TYPEDEFS DECLARATIONS
*******************************************************************************/
typedef void (*Display_t)(void *);

typedef void (*Ctor_Public_Transport_t)(PublicTransport_t*);
typedef void (*CCtor_Public_Transport_t)(PublicTransport_t* public_transport, const PublicTransport_t*);

typedef void (*Dtor_Public_Transport_t)(PublicTransport_t*);
typedef void (*Dispay_Public_Transport_t)(PublicTransport_t* public_transport);

typedef void (*Ctor_Minibus_t)(Minibus_t*, int);
typedef void (*Dtor_Minibus_t)(void*);
typedef void (*Display_Minibus_t)(void*);
typedef void (*MinibusWash_t)(void*, int);

typedef void (*Dtor_Taxi_t)(void*);
typedef void (*Display_Taxi_t)(void*);

typedef void (*Dtor_SpecialTaxi_t)(void *);
typedef void (*Display_SpecialTaxi_t)(void *);

/*******************************************************************************
                        STRUCT DEFINITIONS
*******************************************************************************/
struct PublicTransport_s
{
  void *v_ptr;
  int m_license_plate;
};

/* VTABLE */
struct PublicTransportVTable_s
{
  Dtor_Public_Transport_t Dtor;
  Dispay_Public_Transport_t Display;
};

struct Minibus_s
{
  PublicTransport_t publicTransport;
  int m_numSeats;
};

/* VTABLE */
struct MinibusVTable_s
{
  Dtor_Minibus_t Dtor;
  Display_Minibus_t Display;
  MinibusWash_t Wash;
};

struct Taxi_s
{
  PublicTransport_t publicTransport;
};

/* VTABLE */
struct TaxiVTable_s
{
  Dtor_Taxi_t Dtor;
  Display_Taxi_t Display;
};

struct SpecialTaxi_s
{
  Taxi_t taxi;
};

/* VTABLE */
struct SpecialTaxiVTable_s
{
  Dtor_SpecialTaxi_t Dtor;
	Display_SpecialTaxi_t Display;
};

/*******************************************************************
                        Function Definitions
*******************************************************************/
static int get_ID(PublicTransport_t *public_transport);
void Dtor(void *pt);

void PublicTransportCtor(PublicTransport_t *public_transport);
void PublicTransportCCtor(PublicTransport_t *public_transport, const PublicTransport_t *other);
void PublicTransportDtor(PublicTransport_t *public_transport);
void PublicTransportDisplay(PublicTransport_t *public_transport);
void PrintCount();
void Display(void *);

void Wash(void *pt, int minutes);

void MinibusCtor(Minibus_t* minibus);
void MinibusCCtor(Minibus_t* minibus, const Minibus_t* other_);
void MinibusDtor(void* minibus);
void MinibusDisplay(void* minibus);
void MinibusWash(void* minibus, int minutes);

void TaxiCtor(Taxi_t* taxi);
void TaxiCCtor(Taxi_t* taxi, const Taxi_t* other_);
void TaxiDtor(void *taxi);
void TaxiDisplay(void *taxi);

void PublicTransportToV_Print_Info(PublicTransport_t* public_transport);
void VoidToV_Print_Info();
void MinibusToV_Print_info(Minibus_t * minibus);
PublicTransport_t IntToPT_Print_Info(int i);
void TaxiDisplayExt(Taxi_t taxi);

void SpecialTaxiCtor(SpecialTaxi_t * special_taxi);
void SpecialTaxiCCtor(SpecialTaxi_t * special_taxi, const SpecialTaxi_t *other);
void SpecialTaxiDtor(void *special_taxi);
void SpecialTaxiDisplay(void *special_taxi);

/*******************************************************************
                        VTable Global Variables
*******************************************************************/

PublicTransportVTable_t public_transport_vtable = { PublicTransportDtor, PublicTransportDisplay };
TaxiVTable_t taxi_vtable = { TaxiDtor, TaxiDisplay };
MinibusVTable_t minibus_vtable = { MinibusDtor, MinibusDisplay, MinibusWash };
SpecialTaxiVTable_t special_taxi_vtable = {SpecialTaxiDtor, SpecialTaxiDisplay };

/*******************************************************************
                            Main Function
*******************************************************************/

int main()
{
	Minibus_t m;
	PublicTransport_t temp;

	PublicTransport_t *array[3] = {NULL};
  PublicTransport_t array2[3];

	int i = 0;

  Minibus_t arr2_minibus;
  Taxi_t arr2_taxi;

  PublicTransport_t arr2_pt1;
  PublicTransport_t arr2_pt2;
  PublicTransport_t arr2_pt3;

  Minibus_t m2;

  Minibus_t arr3[4];

  Taxi_t *arr4;

  SpecialTaxi_t st;
  Taxi_t temp_taxi;

	MinibusCtor(&m);
	MinibusToV_Print_info(&m);



	temp = IntToPT_Print_Info(3);
  Display(&(temp));
	Dtor(&temp);


	array[0] = malloc(sizeof(Minibus_t));
	array[1] = malloc(sizeof(Taxi_t));
	array[2] = malloc(sizeof(Minibus_t));

	MinibusCtor((Minibus_t *)(array[0]));
	TaxiCtor((Taxi_t *)(array[1]));
	MinibusCtor((Minibus_t *)(array[2]));

	for (i = 0; i < 3; ++i)
	{
		Display(array[i]);
	}

  for (i = 0; i < 3; ++i)
	{
		Dtor(array[i]);
	}

  MinibusCtor(&arr2_minibus);
  PublicTransportCCtor(&arr2_pt1, &arr2_minibus.publicTransport);
  Dtor(&arr2_minibus);

  TaxiCtor(&arr2_taxi);
  PublicTransportCCtor(&arr2_pt2, &arr2_taxi.publicTransport);
  Dtor(&arr2_taxi);

  PublicTransportCtor(&arr2_pt3);

  array2[0] = arr2_pt1;
  array2[1] = arr2_pt2;
  array2[2] = arr2_pt3;

  for (i = 0; i < 3; ++i)
  {
    Display(&array2[i]);
  }

  PublicTransportToV_Print_Info(&array2[0]);

  PrintCount();

  MinibusCtor(&m2);
  PrintCount();

  for (i = 0; i < 4; ++i)
  {
    MinibusCtor(&arr3[i]);
  }

  arr4 = malloc(4 * sizeof(Taxi_t));

  TaxiCtor(&arr4[0]);
  TaxiCtor(&arr4[1]);
  TaxiCtor(&arr4[2]);
  TaxiCtor(&arr4[3]);

  Dtor(&arr4[3]);
  Dtor(&arr4[2]);
  Dtor(&arr4[1]);
  Dtor(&arr4[0]);

  printf("%d\n", MAX_FUNC(1,2));
  printf("%d\n", MAX_FUNC(1,(int)2.0f));

  SpecialTaxiCtor(&st);
  TaxiCCtor(&temp_taxi, &st.taxi);
  TaxiDisplayExt(temp_taxi);

  Dtor(&temp_taxi);
  Dtor(&st);


  Dtor(&arr3[3]);
  Dtor(&arr3[2]);
  Dtor(&arr3[1]);
  Dtor(&arr3[0]);

  Dtor(&m2);

  Dtor(&array2[2]);
  Dtor(&array2[1]);
  Dtor(&array2[0]);

  Dtor(&m);

  return 0;
}

/*******************************************************************
                                FUNCTIONS
*******************************************************************/

void PrintCount()
{
  printf("s_count: %d\n", public_transport_g_count);
}

/*                    PublicTransport                              */
void PublicTransportCtor(PublicTransport_t *public_transport)
{
  ++public_transport_g_count;
  public_transport->m_license_plate = public_transport_g_count;
  public_transport->v_ptr = &public_transport_vtable;
  printf("PublicTransport::Ctor()%d\n", public_transport->m_license_plate);
}

void PublicTransportDtor(PublicTransport_t *public_transport)
{
  --public_transport_g_count;
  printf("PublicTransport::Dtor()%d\n", (public_transport)->m_license_plate);
}

void PublicTransportCCtor(PublicTransport_t *public_transport, const PublicTransport_t *other)
{
  (void)other;
  ++public_transport_g_count;
  public_transport->m_license_plate = public_transport_g_count;
  public_transport->v_ptr = &public_transport_vtable;
  printf("PublicTransport::CCtor() %d\n", public_transport_g_count);
}

void PublicTransportDisplay(PublicTransport_t *public_transport)
{
  printf("PublicTransport::display(): %d\n", (public_transport)->m_license_plate);
}

static int get_ID(PublicTransport_t *public_transport)
{
    return public_transport->m_license_plate;
}

/*                    Minibus                              */
void MinibusCtor(Minibus_t* minibus)
{
  /*minibus->publicTransport->v_ptr = &minibus_vtable;*/
  /* minibus->publicTransport.v_ptr->publicTransportVTable(minibus->publicTransport);*/
  PublicTransportCtor(&(minibus->publicTransport));
  minibus->publicTransport.v_ptr = &minibus_vtable;

  minibus->m_numSeats = 20;

  printf("Minibus::Ctor()\n");
}

void MinibusCCtor(Minibus_t* minibus, const Minibus_t* other_)
{
    PublicTransportCCtor(&(minibus->publicTransport), &(other_->publicTransport));
    minibus->publicTransport.v_ptr = &minibus_vtable;
		printf("Minibus::CCtor()\n");
    minibus->m_numSeats = other_->m_numSeats;
}

void MinibusDtor(void* minibus)
{
  printf("Minibus::Dtor()\n");
  ((Minibus_t *)minibus)->publicTransport.v_ptr = &public_transport_vtable;

  ((PublicTransportVTable_t *)(((Minibus_t *)minibus)->publicTransport.v_ptr))->Dtor(&(((Minibus_t *)minibus)->publicTransport));  /* How to dereference func pointer?? */
}

void MinibusDisplay(void* minibus)
{
  printf("Minibus::display() ID:%d num seats:%d\n", get_ID(&(((Minibus_t *)minibus)->publicTransport)), ((Minibus_t *)minibus)->m_numSeats);
}

void Display(void *pt)
{
  (((PublicTransportVTable_t *)(((PublicTransport_t *)pt))->v_ptr))->Display(pt);
}

void Wash(void *pt, int minutes)
{
  (((MinibusVTable_t *)(((PublicTransport_t *)pt))->v_ptr))->Wash(pt, minutes);
}

void MinibusWash(void* minibus, int minutes)
{
  printf("Minibus::wash(%d) ID:%d\n", minutes, get_ID(&(((Minibus_t *)minibus)->publicTransport)));
}

void Dtor(void *pt)
{
  (((PublicTransportVTable_t *)(((PublicTransport_t *)pt))->v_ptr))->Dtor(pt);
  /*(((PublicTransportVTable_t *)(((PublicTransport_t *)pt))->v_ptr))->PublicTransportDtor(pt);*/
}

void TaxiCtor(Taxi_t* taxi)
{
  PublicTransportCtor(&(taxi->publicTransport));
  printf("Taxi::Ctor()\n");
  taxi->publicTransport.v_ptr = &taxi_vtable;
}

void TaxiCCtor(Taxi_t* taxi, const Taxi_t* other_)
{
    PublicTransportCCtor(&(taxi->publicTransport), &(other_->publicTransport));
    taxi->publicTransport.v_ptr = &taxi_vtable;
    printf("Taxi::CCtor()\n");
}

void TaxiDtor(void *taxi)
{
  ((Taxi_t *)taxi)->publicTransport.v_ptr = &public_transport_vtable;
	printf("Taxi::Dtor()\n");

  ((PublicTransportVTable_t *)(((Taxi_t *)taxi)->publicTransport.v_ptr))->Dtor(&(((Taxi_t *)taxi)->publicTransport));
}

void TaxiDisplay(void *taxi)
{
  printf("Taxi::display() ID:%d\n", get_ID(&(((Taxi_t *)taxi)->publicTransport)));
}

void SpecialTaxiCtor(SpecialTaxi_t * special_taxi)
{
    TaxiCtor(&(special_taxi->taxi));
		printf("SpecialTaxi::Ctor()\n");
		special_taxi->taxi.publicTransport.v_ptr = &special_taxi_vtable;
}

void SpecialTaxiCCtor(SpecialTaxi_t * special_taxi, const SpecialTaxi_t *other)
{
	printf("SpecialTaxi::CCtor()\n");
	TaxiCCtor(&(special_taxi->taxi), &(other->taxi));
  special_taxi->taxi.publicTransport.v_ptr = &special_taxi_vtable;
}

void SpecialTaxiDtor(void *special_taxi)
{
	((SpecialTaxi_t *)special_taxi)->taxi.publicTransport.v_ptr = &taxi_vtable;
	printf("SpecialTaxi::Dtor()\n");
	((TaxiVTable_t *)(((SpecialTaxi_t *)special_taxi)->taxi.publicTransport.v_ptr))->Dtor(&(((SpecialTaxi_t *)special_taxi)->taxi.publicTransport));
}

void SpecialTaxiDisplay(void *special_taxi)
{
	printf("SpecialTaxi::display() ID:%d\n", get_ID(&(((SpecialTaxi_t *)special_taxi)->taxi.publicTransport)));
}


void PublicTransportToV_Print_Info(PublicTransport_t* public_transport)
{
  Display(public_transport);
}

void VoidToV_Print_Info()
{
  PrintCount();
}

void MinibusToV_Print_info(Minibus_t * minibus)
{
  Wash(minibus, 3);
}

PublicTransport_t IntToPT_Print_Info(int i)
{
  Minibus_t ret;
  PublicTransport_t ret2;
  MinibusCtor(&ret);
	printf("print_info(int i)\n");
  Display(&ret);
  PublicTransportCCtor(&ret2, &(ret.publicTransport));
  Dtor(&ret);

  return ret2;
}

void TaxiDisplayExt(Taxi_t taxi)
{
  Display(&taxi);
}
