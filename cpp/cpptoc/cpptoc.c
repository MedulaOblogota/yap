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
typedef PublicTransport_t Taxi_t;
typedef struct TaxiVTable_s TaxiVTable_t;
typedef Taxi_t SpecialTaxi_t;
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
typedef void (*Dtor_Minibus_t)(Minibus_t*);
typedef void (*Display_Minibus_t)(Minibus_t*);
typedef void (*Minibus__Wash_t)(Minibus_t*, int);

typedef void (*Dtor_Taxi_t)(Taxi_t*);
typedef void (*Display_Taxi_t)(Taxi_t*);

typedef void (*Dtor_SpecialTaxi_t)(SpecialTaxi_t *);
typedef void (*Display_SpecialTaxi_t)(SpecialTaxi_t *);

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
  /* Dtor_Minibus_t Dtor;
   Display_Minibus_t Display;*/
  PublicTransportVTable_t publicTransportVTable;
  Minibus__Wash_t Wash;
};

/* VTABLE */
struct TaxiVTable_s
{
  PublicTransportVTable_t publicTransportVTable;
  /* Dtor_Taxi_t Dtor;
   Display_Taxi_t Display;*/
};

/* VTABLE */
struct SpecialTaxiVTable_s
{
  PublicTransportVTable_t publicTransportVTable;
  /* Dtor_SpecialTaxi_t Dtor;
	Display_SpecialTaxi_t Display;*/
};

/*******************************************************************
                        Function Definitions
*******************************************************************/
static int get_ID(PublicTransport_t *public_transport);
void Dtor(void *pt);

void PublicTransport__Ctor(PublicTransport_t *public_transport);
void PublicTransport__CCtor(PublicTransport_t *public_transport, const PublicTransport_t *other);
void PublicTransport__Dtor(PublicTransport_t *public_transport);
void PublicTransport__Display(PublicTransport_t *public_transport);

void PrintCount();
void Display(void *);
void Wash(void *pt, int minutes);

void Minibus__Ctor(Minibus_t* minibus);
void Minibus__CCtor(Minibus_t* minibus, const Minibus_t* other_);
void Minibus__Dtor(Minibus_t* minibus);
void Minibus__Display(Minibus_t* minibus);
void Minibus__Wash(Minibus_t* minibus, int minutes);

void Taxi__Ctor(Taxi_t* taxi);
void Taxi__CCtor(Taxi_t* taxi, const Taxi_t* other_);
void Taxi__Dtor(Taxi_t* taxi);
void Taxi__Display(Taxi_t *taxi);

void PublicTransportToV_Print_Info(PublicTransport_t* public_transport);
void VoidToV_Print_Info();
void MinibusToV_Print_info(Minibus_t * minibus);
void IntToPT_Print_Info(int i, PublicTransport_t *public_transport);
void TaxiDisplayExt(Taxi_t *taxi);

void SpecialTaxi__Ctor(SpecialTaxi_t * special_taxi);
void SpecialTaxi__CCtor(SpecialTaxi_t * special_taxi, const SpecialTaxi_t *other);
void SpecialTaxi__Dtor(SpecialTaxi_t *special_taxi);
void SpecialTaxi__Display(SpecialTaxi_t *special_taxi);

/*******************************************************************
                        VTable Global Variables
*******************************************************************/

PublicTransportVTable_t public_transport_vtable = { PublicTransport__Dtor, PublicTransport__Display };
TaxiVTable_t taxi_vtable = { {(Dtor_Public_Transport_t)Taxi__Dtor, (Dispay_Public_Transport_t)Taxi__Display} };
MinibusVTable_t minibus_vtable = { (Dtor_Public_Transport_t)Minibus__Dtor, (Dispay_Public_Transport_t)Minibus__Display, Minibus__Wash };
SpecialTaxiVTable_t special_taxi_vtable = {(Dtor_Public_Transport_t)SpecialTaxi__Dtor, (Dispay_Public_Transport_t)SpecialTaxi__Display };

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

  size_t arr_size = 4;
  size_t *sizet_ptr;

	Minibus__Ctor(&m);
	MinibusToV_Print_info(&m);

	IntToPT_Print_Info(3, &temp);
  PublicTransport__Display(&(temp));
	PublicTransport__Dtor(&temp);


	array[0] = (PublicTransport_t *)malloc(sizeof(Minibus_t));
	array[1] = (PublicTransport_t *)malloc(sizeof(Taxi_t));
	array[2] = (PublicTransport_t *)malloc(sizeof(Minibus_t));

	Minibus__Ctor((Minibus_t *)(array[0]));
	Taxi__Ctor((Taxi_t *)(array[1]));
	Minibus__Ctor((Minibus_t *)(array[2]));

	for (i = 0; i < 3; ++i)
	{
		Display(array[i]);
	}

  for (i = 0; i < 3; ++i)
	{
		Dtor(array[i]);
    free(array[i]);
	}

  Minibus__Ctor(&arr2_minibus);
  PublicTransport__CCtor(&arr2_pt1, &arr2_minibus.publicTransport);
  Minibus__Dtor(&arr2_minibus);

  Taxi__Ctor(&arr2_taxi);
  PublicTransport__CCtor(&arr2_pt2, &arr2_taxi);
  Taxi__Dtor(&arr2_taxi);

  PublicTransport__Ctor(&arr2_pt3);

  array2[0] = arr2_pt1;
  array2[1] = arr2_pt2;
  array2[2] = arr2_pt3;

  for (i = 0; i < 3; ++i)
  {
      PublicTransport__Display(array2 + i);
  }

  PublicTransportToV_Print_Info(&array2[0]);

  PrintCount();

  Minibus__Ctor(&m2);
  PrintCount();

  for (i = 0; i < 4; ++i)
  {
    Minibus__Ctor(&arr3[i]);
  }

  arr4 = (Taxi_t *)malloc(arr_size * sizeof(Taxi_t) + sizeof(size_t));

  sizet_ptr = (size_t *)arr4;
  *sizet_ptr = arr_size;
  ++sizet_ptr;
  arr4 = (Taxi_t *)sizet_ptr;
  for (i = 0; i < arr_size; ++i)
  {
    Taxi__Ctor(arr4 + i);
  }

  arr_size = *((size_t *)arr4 - 1);
  for (i = arr_size - 1; i >= 0; --i)
  {
    Taxi__Dtor(arr4 + i);
  }
  free((size_t *)arr4 - 1);

  printf("%d\n", 1 > 2 ? 1 : 2);
  printf("%d\n", (int)(1 > 2 ? 1 : 2));

  SpecialTaxi__Ctor(&st);
  Taxi__CCtor(&temp_taxi, &st);
  TaxiDisplayExt(&temp_taxi);

  Taxi__Dtor(&temp_taxi);

  SpecialTaxi__Dtor(&st);
/*
  Minibus__Dtor(&arr3[3]);
  Minibus__Dtor(&arr3[2]);
  Minibus__Dtor(&arr3[1]);
*/
  for (i = 3; i >= 0; --i)
  {
    Minibus__Dtor(&arr3[i]);
  }

  Minibus__Dtor(&m2);

  PublicTransport__Dtor(&array2[2]);
  PublicTransport__Dtor(&array2[1]);
  PublicTransport__Dtor(&array2[0]);

  Minibus__Dtor(&m);

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
void PublicTransport__Ctor(PublicTransport_t *public_transport)
{
  ++public_transport_g_count;
  public_transport->m_license_plate = public_transport_g_count;
  public_transport->v_ptr = &public_transport_vtable;
  printf("PublicTransport::Ctor()%d\n", public_transport->m_license_plate);
}

void PublicTransport__Dtor(PublicTransport_t *public_transport)
{
  --public_transport_g_count;
  printf("PublicTransport::Dtor()%d\n", (public_transport)->m_license_plate);
}

void PublicTransport__CCtor(PublicTransport_t *public_transport, const PublicTransport_t *other)
{
  (void)other;
  ++public_transport_g_count;
  public_transport->m_license_plate = public_transport_g_count;
  public_transport->v_ptr = &public_transport_vtable;
  printf("PublicTransport::CCtor() %d\n", public_transport_g_count);
}

void PublicTransport__Display(PublicTransport_t *public_transport)
{
  printf("PublicTransport::display(): %d\n", (public_transport)->m_license_plate);
}

static int get_ID(PublicTransport_t *public_transport)
{
    return public_transport->m_license_plate;
}

/*                    Minibus                              */
void Minibus__Ctor(Minibus_t* minibus)
{
  /*minibus->publicTransport->v_ptr = &minibus_vtable;*/
  /* minibus->publicTransport.v_ptr->publicTransportVTable(minibus->publicTransport);*/
  PublicTransport__Ctor(&(minibus->publicTransport));
  minibus->publicTransport.v_ptr = &minibus_vtable;

  minibus->m_numSeats = 20;

  printf("Minibus::Ctor()\n");
}

void Minibus__CCtor(Minibus_t* minibus, const Minibus_t* other_)
{
    PublicTransport__CCtor(&(minibus->publicTransport), &(other_->publicTransport));
    minibus->publicTransport.v_ptr = &minibus_vtable;
		printf("Minibus::CCtor()\n");
    minibus->m_numSeats = other_->m_numSeats;
}

void Minibus__Dtor(Minibus_t* minibus)
{
  printf("Minibus::Dtor()\n");
  (minibus)->publicTransport.v_ptr = &public_transport_vtable;

  ((PublicTransportVTable_t *)((minibus)->publicTransport.v_ptr))->Dtor((((PublicTransport_t *)minibus)));  /* How to dereference func pointer?? */
}

void Minibus__Display(Minibus_t* minibus)
{
  printf("Minibus::display() ID:%d num seats:%d\n", get_ID(&((minibus)->publicTransport)), (minibus)->m_numSeats);
}

void Display(void *pt)
{
  /* **(PublicTransportVTable_t *)pt->Display((PublicTransport_t *)pt);*/
  ((PublicTransportVTable_t *)(((PublicTransport_t *)pt)->v_ptr))->Display((PublicTransport_t *)pt);
  /*(((PublicTransportVTable_t *)(((PublicTransport_t *)pt))->v_ptr))->Display(pt);*/
}

void Wash(void *pt, int minutes)
{
  ((MinibusVTable_t *)(((PublicTransport_t *)pt)->v_ptr))->Wash((Minibus_t *)pt, minutes);
/*  (((MinibusVTable_t *)(((PublicTransport_t *)pt))->v_ptr))->Wash(pt, minutes);*/
}

void Minibus__Wash(Minibus_t* minibus, int minutes)
{
  printf("Minibus::wash(%d) ID:%d\n", minutes, get_ID(&((minibus)->publicTransport)));
}

void Dtor(void *pt)
{
  ((PublicTransportVTable_t *)(((PublicTransport_t *)pt)->v_ptr))->Dtor((PublicTransport_t *)pt);
/*  (((PublicTransportVTable_t *)(((PublicTransport_t *)pt))->v_ptr))->Dtor(pt);*/
  /*(((PublicTransportVTable_t *)(((PublicTransport_t *)pt))->v_ptr))->PublicTransport__Dtor(pt);*/
}

void Taxi__Ctor(Taxi_t* taxi)
{
  PublicTransport__Ctor((taxi));
  printf("Taxi::Ctor()\n");
  taxi->v_ptr = &taxi_vtable;
}

void Taxi__CCtor(Taxi_t* taxi, const Taxi_t* other_)
{
    PublicTransport__CCtor((taxi), other_);
    taxi->v_ptr = &taxi_vtable;
    printf("Taxi::CCtor()\n");
}

void Taxi__Dtor(Taxi_t *taxi)
{
  (taxi)->v_ptr = &public_transport_vtable;
	printf("Taxi::Dtor()\n");

  ((PublicTransportVTable_t *)((taxi)->v_ptr))->Dtor(((taxi)));
}

void Taxi__Display(Taxi_t* taxi)
{
  printf("Taxi::display() ID:%d\n", get_ID(((taxi))));
}

void SpecialTaxi__Ctor(SpecialTaxi_t * special_taxi)
{
    Taxi__Ctor((special_taxi));
		printf("SpecialTaxi::Ctor()\n");
		special_taxi->v_ptr = &special_taxi_vtable;
}

void SpecialTaxi__CCtor(SpecialTaxi_t * special_taxi, const SpecialTaxi_t *other)
{
	printf("SpecialTaxi::CCtor()\n");
	Taxi__CCtor((special_taxi), (other));
  special_taxi->v_ptr = &special_taxi_vtable;
}

void SpecialTaxi__Dtor(SpecialTaxi_t *special_taxi)
{
	(special_taxi)->v_ptr = &taxi_vtable;
	printf("SpecialTaxi::Dtor()\n");
  ((PublicTransportVTable_t *)(special_taxi->v_ptr))->Dtor(special_taxi);
	/*((TaxiVTable_t *)((special_taxi)->taxi.publicTransport.v_ptr))->Dtor(&(special_taxi->taxi));*/
}

void SpecialTaxi__Display(SpecialTaxi_t *special_taxi)
{
	printf("SpecialTaxi::display() ID:%d\n", get_ID(((special_taxi))));
}


void PublicTransportToV_Print_Info(PublicTransport_t* public_transport)
{
  Display(public_transport);
  /*PublicTransport__Dtor(public_transport);*/
}

void VoidToV_Print_Info()
{
  PrintCount();
}

void MinibusToV_Print_info(Minibus_t * minibus)
{
  Wash(minibus, 3);
/*  Minibus__Dtor(minibus);*/
}

void IntToPT_Print_Info(int i, PublicTransport_t *public_transport)
{
  Minibus_t ret;
  // PublicTransport_t ret2;
  Minibus__Ctor(&ret);
	printf("print_info(int i)\n");
  Display(&ret);
  PublicTransport__CCtor(public_transport, &(ret.publicTransport));
  Minibus__Dtor(&ret);
  /*PublicTransport__Dtor(public_transport);*/

  return;
}

void TaxiDisplayExt(Taxi_t *taxi)
{
  Display(taxi);
  /*Taxi__Dtor(taxi);*/
}
