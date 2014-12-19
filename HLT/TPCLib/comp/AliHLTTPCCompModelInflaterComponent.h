// XEmacs -*-C++-*-
// $Id$

#ifndef ALIHLTTPCCOMPMODELINFLATERCOMPONENT_H
#define ALIHLTTPCCOMPMODELINFLATERCOMPONENT_H
//* This file is property of and copyright by the ALICE HLT Project        * 
//* ALICE Experiment at CERN, All rights reserved.                         *
//* See cxx source for full Copyright notice                               *

/** @file   AliHLTTPCCompModelInflaterComponent.h
    @author Timm Steinbeck
    @date   
    @brief  Declaration of a copy component. */


#include "AliHLTProcessor.h"
#include "AliHLTTPCCompModelInflater.h"
#include "AliHLTTPCCompModelConverter.h"

/**
 * @class AliHLTTPCCompModelInflaterComponent
 * @brief A dummy HLT processing component. 
 *
 * An implementiation of an inflater component 
 * to process the inflation after the 
 * Vestbo compression which is then followed by the
 * deconversion component to retrieve the original
 * standard cluster track format of the input data
 * @ingroup alihlt_tpc
 */
class AliHLTTPCCompModelInflaterComponent : public AliHLTProcessor
    {
    public:

      /** standard constructor */
      AliHLTTPCCompModelInflaterComponent();
      /** standard destructor */
      virtual ~AliHLTTPCCompModelInflaterComponent();
      
      // Public functions to implement AliHLTComponent's interface.
      // These functions are required for the registration process
       
      /** function to get component id 
       * @return const char* pointer to componentid
       */
      const char* GetComponentID();

      /** function to get input data types
       * @param list vecotr of AliHLTComponent_DataType
       */
      void GetInputDataTypes( vector<AliHLTComponent_DataType>& list);

      /** function to get output data type
       * @return AliHLTComponent_DataType
       */
      AliHLTComponent_DataType GetOutputDataType();

      /** function to get output data size
       * @param constBase address of an unsigned long
       * @param inputMultiplier address of a double
       */
      virtual void GetOutputDataSize( unsigned long& constBase, double& inputMultiplier );

      /** spawn function
       * @return AliHLTComponent* pointer to instance
       */
      AliHLTComponent* Spawn();
	
    protected:
	
	// Protected functions to implement AliHLTComponent's interface.
	// These functions provide initialization as well as the actual processing
	// capabilities of the component. 

      /** initialisation function
       * @param argc integer counting number of input arguments
       * @param argv const char** for parameter values
       * @return zero upon success
       */
      int DoInit( int argc, const char** argv );

      /** deinitialisation function
       * @return zero upon success
       */
      int DoDeinit();

      /** do event function
       * @param evtData      const AliHLTComponent_EventData& to event data
       * @param blocks       const AliHLTComponent_BlockData* to blocks of event data
       * @param trigData     AliHLTComponent_TriggerData& of trigger data
       * @param outputPtr    AliHLTUInt8_t* pointer to output data
       * @param size         AliHLTUInt32_t& of output size
       * @param outputBlocks vector<AliHLTComponent_BlockData>& of output block data
       * @return zero upon success
       */
      int DoEvent( const AliHLTComponent_EventData& evtData, const AliHLTComponent_BlockData* blocks, 
		   AliHLTComponent_TriggerData& trigData, AliHLTUInt8_t* outputPtr, 
		   AliHLTUInt32_t& size, vector<AliHLTComponent_BlockData>& outputBlocks );
      
      /** member variable for instance of model inflater class */
      AliHLTTPCCompModelInflater fModelInflater; // member variable for instance of model inflater class
      
    private:

	ClassDef(AliHLTTPCCompModelInflaterComponent, 0)

    };
#endif