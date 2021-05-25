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
typedef struct Minibus_s Minibus_t;
typedef PublicTransport_t Taxi_t;
typedef Taxi_t SpecialTaxi_t;
typedef struct PublicConvoy_s PublicConvoy_t;

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

typedef void (*Dtor_PublicConvoy_t)(PublicConvoy_t *);
typedef void (*Display_PublicConvoy_t)(PublicConvoy_t *);


typedef void (*VTableFunc)(PublicTransport_t *);

/*******************************************************************************
                        STRUCT DEFINITIONS
*******************************************************************************/
struct PublicTransport_s
{
  void *v_ptr;
  int m_license_plate;
};

struct Minibus_s
{
  PublicTransport_t publicTransport;
  int m_numSeats;
};

struct PublicConvoy_s
{
  PublicTransport_t publicTransport;

  PublicTransport_t *m_pt1;
  PublicTransport_t *m_pt2;
  Minibus_t m_m;
  Taxi_t m_t;
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

void PublicConvoy__Ctor(PublicConvoy_t *public_convoy);
void PublicConvoy__CCtor(PublicConvoy_t *public_convoy,const  PublicConvoy_t *other_);
void PublicConvoy__Dtor(PublicConvoy_t *public_convoy);
void PublicConvoy__Display(PublicConvoy_t *public_convoy);

/*******************************************************************
                        VTable Global Variables
*******************************************************************/

VTableFunc public_transport_vtable[] = { (VTableFunc)PublicTransport__Dtor, (VTableFunc)PublicTransport__Display };
VTableFunc taxi_vtable[] = {(VTableFunc)Taxi__Dtor, (VTableFunc)Taxi__Display};
VTableFunc minibus_vtable[] = { (VTableFunc)Minibus__Dtor, (VTableFunc)Minibus__Display, (VTableFunc)Minibus__Wash };
VTableFunc special_taxi_vtable[] = {(VTableFunc)SpecialTaxi__Dtor, (VTableFunc)SpecialTaxi__Display };
VTableFunc public_convoy_vtable[] = {(VTableFunc)PublicConvoy__Dtor, (VTableFunc)PublicConvoy__Display};

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

  PublicConvoy_t *ts1;
  PublicConvoy_t *ts2;

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


  ts1 = malloc(sizeof(PublicConvoy_t));
  PublicConvoy__Ctor(ts1);

  ts2 = malloc(sizeof(PublicConvoy_t));
  PublicConvoy__CCtor(ts2, ts1);

  PublicConvoy__Display(ts1);
  PublicConvoy__Display(ts2);

  PublicConvoy__Dtor(ts1);
  free(ts1);

   PublicConvoy__Display(ts2);

   PublicConvoy__Dtor(ts2);
free(ts2);





  SpecialTaxi__Dtor(&st);

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

  (((VTableFunc *)(minibus->publicTransport.v_ptr))[0])((PublicTransport_t *)minibus);

}

void Minibus__Display(Minibus_t* minibus)
{
  printf("Minibus::display() ID:%d num seats:%d\n", get_ID(&((minibus)->publicTransport)), (minibus)->m_numSeats);
}

void Display(void *pt)
{
  (((VTableFunc *)(((PublicTransport_t *)pt)->v_ptr))[1])((PublicTransport_t *)pt);
}

void Wash(void *pt, int minutes)
{
  ((Minibus__Wash_t )(((VTableFunc *)(((PublicTransport_t *)pt)->v_ptr) )[2] ))((Minibus_t *)pt, minutes);
}

void Minibus__Wash(Minibus_t* minibus, int minutes)
{
  printf("Minibus::wash(%d) ID:%d\n", minutes, get_ID(&(minibus->publicTransport)));
}

void Dtor(void *pt)
{
  (((VTableFunc *)(((PublicTransport_t *)pt)->v_ptr))[0])((PublicTransport_t *)pt);
}

void Taxi__Ctor(Taxi_t* taxi)
{
  PublicTransport__Ctor(taxi);
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

  (((VTableFunc *)(taxi->v_ptr))[0])((PublicTransport_t *)taxi);

}

void Taxi__Display(Taxi_t* taxi)
{
  printf("Taxi::display() ID:%d\n", get_ID(taxi));
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

  (((VTableFunc *)(special_taxi->v_ptr))[0])((PublicTransport_t *)special_taxi);
}

void SpecialTaxi__Display(SpecialTaxi_t *special_taxi)
{
	printf("SpecialTaxi::display() ID:%d\n", get_ID(special_taxi));
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

void IntToPT_Print_Info(int i, PublicTransport_t *public_transport)
{
  Minibus_t ret;
  (void)i;
  Minibus__Ctor(&ret);
	printf("print_info(int i)\n");
  Display(&ret);
  PublicTransport__CCtor(public_transport, &(ret.publicTransport));
  Minibus__Dtor(&ret);
}

void TaxiDisplayExt(Taxi_t *taxi)
{
  Display(taxi);
}

void PublicConvoy__Ctor(PublicConvoy_t* public_convoy)
{
  PublicTransport__Ctor(&(public_convoy->publicTransport));

  public_convoy->m_pt1 = (PublicTransport_t *)malloc(sizeof(Minibus_t));
  Minibus__Ctor((Minibus_t *)(public_convoy->m_pt1));

  public_convoy->m_pt2 = (PublicTransport_t *)malloc(sizeof(Taxi_t));
  Taxi__Ctor((Taxi_t *)(public_convoy->m_pt2));

  Minibus__Ctor(&(public_convoy->m_m));
  Taxi__Ctor(&(public_convoy->m_t));
}

void PublicConvoy__CCtor(PublicConvoy_t* public_convoy, const PublicConvoy_t* other_)
{
  PublicTransport__CCtor(&(public_convoy->publicTransport), &(other_->publicTransport));

  public_convoy->m_pt1 = malloc(sizeof(Minibus_t));
  Minibus__CCtor((Minibus_t *)(public_convoy->m_pt1), (Minibus_t *)(other_->m_pt1));

  public_convoy->m_pt2 = malloc(sizeof(Taxi_t));
  Taxi__CCtor((Taxi_t *)(public_convoy->m_pt2), (Taxi_t *)(other_->m_pt2));

  Minibus__CCtor(&(public_convoy->m_m), &(other_->m_m));
  Taxi__CCtor(&(public_convoy->m_t), &(other_->m_t));
}

void PublicConvoy__Dtor(PublicConvoy_t* public_convoy)
{
  public_convoy->publicTransport.v_ptr = &public_transport_vtable;

  Minibus__Dtor((Minibus_t *)(public_convoy->m_pt1));
  Taxi__Dtor((Taxi_t *)(public_convoy->m_pt2));

  Taxi__Dtor(&(public_convoy->m_t));
  Minibus__Dtor(&(public_convoy->m_m));
  /* free(public_convoy->m_pt1);   public_convoy->m_pt1 = NULL;*/

  /* free(public_convoy->m_pt2);   public_convoy->m_pt2 = NULL;*/


  (((VTableFunc *)(public_convoy->publicTransport.v_ptr))[0])((PublicTransport_t *)public_convoy);
}

void PublicConvoy__Display(PublicConvoy_t* public_convoy)
{
  Minibus__Display((Minibus_t *)(public_convoy->m_pt1));
  Taxi__Display((Taxi_t *)(public_convoy->m_pt2));
  Minibus__Display(&(public_convoy->m_m));
  Taxi__Display(&(public_convoy->m_t));
}
