USE [DB_FIXED_ASSET]
GO
/****** Object:  StoredProcedure [dbo].[Sp_Room_Save]    Script Date: 05-Feb-19 4:00:44 PM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
ALTER PROCEDURE [dbo].[Sp_Room_Save] -- !!! สำคัญ ต้องเปลี่ยน Activity type
	@Epc nvarchar(50),	
	@Tid nvarchar(50),
	@RoomCode nvarchar(50),
	@RoomDescription nvarchar(1000),	
	@RowCount int output,
	@MessageResult nvarchar(100) output
AS
BEGIN

	-- ===================================================================================
	-- STATE-1: VALIDATION
	--             - CHECK NULL
	--             - CHECK EMPTY
	-- ===================================================================================
	
	-- TID
	IF @Tid is NULL
	begin
		set @RowCount = 0;
		set @MessageResult = 'Invalid TID! TID cannot be null.';
		return -2;
	end	
	IF @Tid=''
	begin
		set @RowCount = 0;
		set @MessageResult = 'Invalid TID! TID cannot be empty.';
		return -2;
	end	
	-- FID
	IF @RoomCode is NULL
	begin
		set @RowCount = 0;
		set @MessageResult = 'Invalid Room Code! Room Code cannot be null.';
		return -2;
	end	
	IF @RoomCode=''
	begin
		set @RowCount = 0;
		set @MessageResult = 'Invalid Room Code! Room Code cannot be empty.';
		return -2;
	end	

	-- ===================================================================================
	-- STATE-2: SAVE BY INSERT OR UPDATE
	-- ===================================================================================	
	Declare @Id int = null;
	select top 1 @Id = R.ID from TB_ROOM R WHERE R.ROOM_CODE = @RoomCode; -- CHECK EXIST TID

	if @Id is null or @Id=0 /* CRITERIA FOR INSERT NEW*/
	begin
		
		begin try
				
			-- DO INSERT
			print 'INSERTION AS NEW RECORD...'

			INSERT INTO TB_ROOM
			(
				ROOM_EPC,
				ROOM_TID,
				ROOM_CODE,
				ROOM_DESCRIPTION
			) 
			VALUES 
			(
				@Epc,
				@Tid,
				@RoomCode,
				@RoomDescription
			)
			
			set @RowCount = @@ROWCOUNT;
			
			-- RETURN
			IF @RowCount>0 -- INSERTION SUCCESS
			BEGIN
				print 'INSERTION SUCCESS.'
				set @MessageResult = 'Insertion a new Room success.';
				return 0;
			END
			ELSE -- NOTHING
			BEGIN
				print 'INSERTION NOTHING'
				set @MessageResult = 'There is no any save activity.';
				return -1;
			END
		end try
		begin catch
			set @RowCount = 0;
			set @MessageResult = ERROR_MESSAGE();
			return -2;
		end catch
		
	END
	else -- do update the asset recode by TID
	begin
		
		begin try

			print 'UPDATING...'
			
			update TB_ROOM
			set 
				ROOM_EPC = @Epc,
				ROOM_TID = @Tid,
				ROOM_CODE = @RoomCode,
				ROOM_DESCRIPTION = @RoomDescription
			where ROOM_CODE=@RoomCode;

			set @RowCount=@@ROWCOUNT;

			-- RETURN
			IF @RowCount>0 -- UPDATED
			BEGIN
				PRINT 'UPDATING SUCCESS';
				set @MessageResult = 'Room data updated successful.';
				return 0
			END
			ELSE -- NOTHING
			BEGIN
				PRINT 'Nothing updated';
				set @MessageResult = 'There is no any save activity.';
				return -1
			END

		end try
		begin catch
			set @RowCount = 0;
			set @MessageResult = ERROR_MESSAGE();
			return -2;
		end catch

	end

	-- safety
	return -99;

/* END */
END
