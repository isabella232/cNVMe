/*
This file is part of cNVMe and is released under the MIT License
(C) - Charles Machalow - 2017
Command.h - A header file for the NVMe Command
*/

#pragma once

#include "Types.h"

namespace cnvme
{
	namespace command
	{
		/// <summary>
		/// Command DWord 0
		/// </summary>
		typedef struct DWORD0
		{
			UINT_32 OPC : 8; // Opcode
			UINT_32 FUSE : 2; // Fused Operation
			UINT_32 Reserved0 : 4; // Reserved
			UINT_32 PSDT : 2; // PRP or SGL for Data Transfer
			UINT_32 CID : 16; // Command Identifier

			std::string toString() const;
		}DWORD0, *PDWORD0;
		static_assert(sizeof(DWORD0) == 4, "DWORD0 should be 4 byte(s) in size.");

		/// <summary>
		/// Metadata pointer
		/// </summary>
		typedef struct MPTR
		{
			union
			{
				UINT_32 MPTR1; // Metadata Pointer 1
				UINT_32 DWord4;
			};

			union
			{
				UINT_32 MPTR2; // Metadata Pointer 2
				UINT_32 DWord5;
			};

			std::string toString() const;
		}MPTR, *PMPTR;
		static_assert(sizeof(MPTR) == 8, "MPTR should be 8 byte(s) in size.");

		/// <summary>
		/// Data pointer
		/// </summary>
		typedef struct DPTR
		{
			union
			{
				UINT_64 DPTR1; // Data Pointer 1
				struct
				{
					UINT_32 DWord6;
					UINT_32 DWord7;
				};
			};

			union
			{
				UINT_32 DPTR2; // Data Pointer 2
				struct
				{
					UINT_32 DWord8;
					UINT_32 DWord9;
				};
			};

			std::string toString() const;
		}DPTR, *PDPTR;
		static_assert(sizeof(DPTR) == 16, "DPTR should be 16 byte(s) in size.");


		/// <summary>
		/// Complete NVMe Command
		/// </summary
		typedef struct NVME_COMMAND
		{
			union
			{
				UINT_32 DWord0;
				DWORD0 DWord0Breakdown;
			};

			union
			{
				UINT_32 NSID; // Namespace Id
				UINT_32 DWord1;
			};

			UINT_32 DWord2; // Reserved
			UINT_32 DWord3; // Reserved

			union
			{
				MPTR MPTR; // Metadata Pointer
				UINT_64 CompleteMPTR;
			};

			union
			{
				DPTR DPTR; // Data Pointer
				UINT_64 SGL1[2]; // Scatter Gather List Entry 1 (placeholder)
			};

			UINT_32 DWord10; // Command Specific DW10
			UINT_32 DWord11; // Command Specific DW11
			UINT_32 DWord12; // Command Specific DW12
			UINT_32 DWord13; // Command Specific DW13
			UINT_32 DWord14; // Command Specific DW14
			UINT_32 DWord15; // Command Specific DW15

			std::string toString() const;
		}NVME_COMMAND, *PNVME_COMMAND;
		static_assert(sizeof(NVME_COMMAND) == 64, "NVME_COMMAND should be 64 byte(s) in size.");

	}
}
