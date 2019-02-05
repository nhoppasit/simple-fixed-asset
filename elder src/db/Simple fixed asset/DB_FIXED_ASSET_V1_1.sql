
CREATE TABLE [dbo].[TB_ASSET](
	[ID] [int] IDENTITY(1,1) NOT NULL,
	[ROOM_CODE] [nvarchar](50) NULL,
	[EPC] [nvarchar](50) NULL,
	[TID] [nvarchar](50) NOT NULL,
	[FID] [nvarchar](50) NULL,
	[ASSET_LABEL] [nvarchar](200) NULL,
	[ASSET_TYPE] [nvarchar](200) NULL,
	[ASSET_DESCRIPTION] [nvarchar](1000) NULL,
	[CREATED_DATE] [datetime] NULL,
	[CREATED_BY] [int] NULL,
	[MODIFIED_DATE] [datetime] NULL,
	[MODIFIED_BY] [int] NULL,
 CONSTRAINT [PK_TB_ASSET] PRIMARY KEY CLUSTERED 
(
	[TID] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY]
GO
/****** Object:  Table [dbo].[TB_ROOM]    Script Date: 9/18/2018 2:07:39 PM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[TB_ROOM](
	[ID] [int] IDENTITY(1,1) NOT NULL,
	[EPC] [nvarchar](50) NULL,
	[TID] [nvarchar](50) NULL,
	[ROOM_CODE] [nvarchar](50) NULL,
	[ROOM_DESCRIPTION] [nvarchar](1000) NULL,
	[CREATED_DATE] [datetime] NULL,
	[CREATED_BY] [int] NULL,
	[MODIFIED_DATE] [datetime] NULL,
	[MODIFIED_BY] [int] NULL,
 CONSTRAINT [PK_TB_ROOM] PRIMARY KEY CLUSTERED 
(
	[ID] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY]
GO
SET IDENTITY_INSERT [dbo].[TB_ASSET] ON 
GO
INSERT [dbo].[TB_ASSET] ([ID], [ROOM_CODE], [EPC], [TID], [FID], [ASSET_LABEL], [ASSET_TYPE], [ASSET_DESCRIPTION], [CREATED_DATE], [CREATED_BY], [MODIFIED_DATE], [MODIFIED_BY]) VALUES (1, NULL, NULL, N'123', N'abc', NULL, NULL, NULL, CAST(N'2018-09-18T00:11:32.220' AS DateTime), 1, CAST(N'2018-09-18T00:11:32.220' AS DateTime), 1)
GO
INSERT [dbo].[TB_ASSET] ([ID], [ROOM_CODE], [EPC], [TID], [FID], [ASSET_LABEL], [ASSET_TYPE], [ASSET_DESCRIPTION], [CREATED_DATE], [CREATED_BY], [MODIFIED_DATE], [MODIFIED_BY]) VALUES (2, NULL, NULL, N'1234', N'abc', NULL, NULL, NULL, CAST(N'2018-09-18T00:11:44.220' AS DateTime), 1, CAST(N'2018-09-18T00:11:44.220' AS DateTime), 1)
GO
INSERT [dbo].[TB_ASSET] ([ID], [ROOM_CODE], [EPC], [TID], [FID], [ASSET_LABEL], [ASSET_TYPE], [ASSET_DESCRIPTION], [CREATED_DATE], [CREATED_BY], [MODIFIED_DATE], [MODIFIED_BY]) VALUES (1005, N'', N'', N'123456', N'abd', N'', N'', N'', CAST(N'2018-09-18T11:30:43.680' AS DateTime), 1, CAST(N'2018-09-18T11:30:51.853' AS DateTime), 1)
GO
INSERT [dbo].[TB_ASSET] ([ID], [ROOM_CODE], [EPC], [TID], [FID], [ASSET_LABEL], [ASSET_TYPE], [ASSET_DESCRIPTION], [CREATED_DATE], [CREATED_BY], [MODIFIED_DATE], [MODIFIED_BY]) VALUES (3, NULL, NULL, N'456', N'WOW', NULL, NULL, NULL, CAST(N'2018-09-18T00:18:47.670' AS DateTime), 1, CAST(N'2018-09-18T00:23:02.480' AS DateTime), 1)
GO
INSERT [dbo].[TB_ASSET] ([ID], [ROOM_CODE], [EPC], [TID], [FID], [ASSET_LABEL], [ASSET_TYPE], [ASSET_DESCRIPTION], [CREATED_DATE], [CREATED_BY], [MODIFIED_DATE], [MODIFIED_BY]) VALUES (4, NULL, NULL, N'4567', N'abc', NULL, NULL, NULL, CAST(N'2018-09-18T00:18:50.397' AS DateTime), 1, CAST(N'2018-09-18T00:20:15.393' AS DateTime), 1)
GO
INSERT [dbo].[TB_ASSET] ([ID], [ROOM_CODE], [EPC], [TID], [FID], [ASSET_LABEL], [ASSET_TYPE], [ASSET_DESCRIPTION], [CREATED_DATE], [CREATED_BY], [MODIFIED_DATE], [MODIFIED_BY]) VALUES (5, NULL, NULL, N'999', N'W333', NULL, NULL, NULL, CAST(N'2018-09-18T00:23:12.630' AS DateTime), 1, CAST(N'2018-09-18T00:23:20.593' AS DateTime), 1)
GO
SET IDENTITY_INSERT [dbo].[TB_ASSET] OFF
GO
/****** Object:  StoredProcedure [dbo].[Sp_Asset_Save]    Script Date: 9/18/2018 2:07:40 PM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE PROCEDURE [dbo].[Sp_Asset_Save] -- !!! สำคัญ ต้องเปลี่ยน Activity type
	@RoomCode nvarchar(50),	
	@Epc nvarchar(50),	
	@Tid nvarchar(50),	
	@Fid nvarchar(50),	
	@AssetLabel nvarchar(200),	
	@AssetType nvarchar(200),	
	@AssetDescription nvarchar(1000),	
	@SystemId int,
	@RowCount int output,
	@MessageResult nvarchar(100) output
AS
BEGIN

	-- ===================================================================================
	-- STATE-1: VALIDATION
	--             - CHECK NULL
	--             - CHECK EMPTY
	-- ===================================================================================
	-- System id
	IF @SystemId is NULL
	begin
		set @RowCount = 0;
		set @MessageResult = 'Invalid system id! System id cannot be null.';
		return -2;
	end	
	IF @SystemId<=0
	begin
		set @RowCount = 0;
		set @MessageResult = 'Invalid system id! system id must more than 0.';
		return -2;
	end	
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
	IF @Fid is NULL
	begin
		set @RowCount = 0;
		set @MessageResult = 'Invalid FID! FID cannot be null.';
		return -2;
	end	
	IF @Fid=''
	begin
		set @RowCount = 0;
		set @MessageResult = 'Invalid FID! FID cannot be empty.';
		return -2;
	end	

	-- ===================================================================================
	-- STATE-2: SAVE BY INSERT OR UPDATE
	-- ===================================================================================	
	Declare @Id int = null;
	select top 1 @Id = T.ID from TB_ASSET T WHERE T.TID = @Tid; -- CHECK EXIST TID

	if @Id is null or @Id=0 /* CRITERIA FOR INSERT NEW*/
	begin
		
		begin try
				
			-- DO INSERT
			print 'INSERTION AS NEW RECORD...'

			INSERT INTO TB_ASSET
			(
				ROOM_CODE,
				EPC,
				TID,
				FID,
				ASSET_LABEL,
				ASSET_TYPE,
				ASSET_DESCRIPTION,
				CREATED_DATE,
				CREATED_BY,
				MODIFIED_DATE,
				MODIFIED_BY
			) 
			VALUES 
			(
				@RoomCode,
				@Epc,
				@Tid,
				@Fid,
				@AssetLabel,
				@AssetType,
				@AssetDescription,
				getdate(),
				@SystemId,
				getdate(),
				@SystemId
			)
			
			set @RowCount = @@ROWCOUNT;
			
			-- RETURN
			IF @RowCount>0 -- INSERTION SUCCESS
			BEGIN
				print 'INSERTION SUCCESS.'
				set @MessageResult = 'Insertion a new asset success.';
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
			
			update TB_ASSET
			set 
				ROOM_CODE = @RoomCode,
				EPC = @Epc,
				FID = @Fid,
				ASSET_LABEL = @AssetLabel,
				ASSET_TYPE = @AssetType,
				ASSET_DESCRIPTION = @AssetDescription,
				MODIFIED_DATE = GETDATE(),
				MODIFIED_BY = @SystemId
			where TID=@Tid;

			set @RowCount=@@ROWCOUNT;

			-- RETURN
			IF @RowCount>0 -- UPDATED
			BEGIN
				PRINT 'UPDATING SUCCESS';
				set @MessageResult = 'Asset data updated successful.';
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
GO
/****** Object:  StoredProcedure [dbo].[Sp_Asset_SearchByFid]    Script Date: 9/18/2018 2:07:40 PM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- =============================================
-- Author:		<Author,,Name>
-- Create date: <Create Date,,>
-- Description:	<Description,,>
-- =============================================
CREATE PROCEDURE [dbo].[Sp_Asset_SearchByFid]
	-- Add the parameters for the stored procedure here
	@FID nvarchar(50),
	@RowCount int output,
	@MessageResult nvarchar(200) OUTPUT
AS
BEGIN			
	-- ===================================================================================
	-- STATE-1: VALIDATION
	-- ===================================================================================	
	-- fid
	IF @FID is NULL
	begin
		print 'Invalid TID! TID cannot be null.';
		-- THROW 50031, 'Invalid TID! TID can not be NULL.', 1;  
		set @RowCount=0;
		set @MessageResult = 'Invalid TID! TID cannot be null.';
		return -2;
	end
	IF @FID = ''
	begin
		print 'Invalid TID! TID cannot be empty.';
		-- THROW 50031, 'Invalid TID! TID can not be NULL.', 1;  
		set @RowCount=0;
		set @MessageResult = 'Invalid TID! TID cannot be empty.';
		return -2;
	end

	-- ===================================================================================
	-- STATE-2: QUERY FROM DATABASE
	-- ===================================================================================
	PRINT 'TID = ' + + RTRIM(CAST(@FID AS nvarchar(50)))
	print 'SELECT and join data from TB_ASSET, TB_ROOM and TB_ASSET_TYPE'

	BEGIN TRY

		SELECT T1.EPC,T1.TID,T1.FID,T1.ASSET_LABEL,T1.ASSET_DESCRIPTION,T1.ASSET_TYPE,T2.ROOM_CODE,T2.ROOM_DESCRIPTION
		from TB_ASSET T1
		LEFT JOIN TB_ROOM T2
		ON T1.ROOM_CODE=T2.ROOM_CODE
		WHERE T1.FID=@FID;
						
		SET @RowCount = @@ROWCOUNT;
			
		print 'Done selection'
		IF @RowCount>0 -- data found.
		BEGIN
			SET @MessageResult = 'Asset found.';
			return 0
		END
		ELSE -- data not found!
		BEGIN
			SET @MessageResult = 'Asset not found!';
			return -1
		END

	END TRY
	BEGIN CATCH
		print 'QUERY ERROR'
		SET @RowCount = 0;
		SET @MessageResult = ERROR_MESSAGE();
		return -2
	END CATCH

	-- SAFETY
	return -99

-- END OF STORE PROCEDURE.
END
GO
/****** Object:  StoredProcedure [dbo].[Sp_Asset_SearchByTid]    Script Date: 9/18/2018 2:07:40 PM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- =============================================
-- Author:		<Author,,Name>
-- Create date: <Create Date,,>
-- Description:	<Description,,>
-- =============================================
CREATE PROCEDURE [dbo].[Sp_Asset_SearchByTid]
	-- Add the parameters for the stored procedure here
	@TID nvarchar(50),
	@RowCount int output,
	@MessageResult nvarchar(200) OUTPUT
AS
BEGIN			
	-- ===================================================================================
	-- STATE-1: VALIDATION
	-- ===================================================================================	
	-- tid
	IF @TID is NULL
	begin
		print 'Invalid TID! TID cannot be null.';
		-- THROW 50031, 'Invalid TID! TID can not be NULL.', 1;  
		set @RowCount=0;
		set @MessageResult = 'Invalid TID! TID cannot be null.';
		return -2;
	end
	-- empty
	IF @TID = ''
	begin
		print 'Invalid TID! TID cannot be empty.';
		-- THROW 50031, 'Invalid TID! TID can not be NULL.', 1;  
		set @RowCount=0;
		set @MessageResult = 'Invalid TID! TID cannot be empty.';
		return -2;
	end

	-- ===================================================================================
	-- STATE-2: QUERY FROM DATABASE
	-- ===================================================================================
	PRINT 'TID = ' + + RTRIM(CAST(@TID AS nvarchar(50)))
	print 'SELECT and join data from TB_ASSET, TB_ROOM and TB_ASSET_TYPE'

	BEGIN TRY

		SELECT T1.EPC,T1.TID,T1.FID,T1.ASSET_LABEL,T1.ASSET_DESCRIPTION,T1.ASSET_TYPE,T2.ROOM_CODE,T2.ROOM_DESCRIPTION
		from TB_ASSET T1
		LEFT JOIN TB_ROOM T2
		ON T1.ROOM_CODE=T2.ROOM_CODE
		WHERE T1.TID=@TID;
						
		SET @RowCount = @@ROWCOUNT;
			
		print 'Done selection'
		IF @RowCount>0 -- data found.
		BEGIN
			SET @MessageResult = 'Asset found.';
			return 0
		END
		ELSE -- data not found!
		BEGIN
			SET @MessageResult = 'Asset not found!';
			return -1
		END

	END TRY
	BEGIN CATCH
		print 'QUERY ERROR'
		SET @RowCount = 0;
		SET @MessageResult = ERROR_MESSAGE();
		return -2
	END CATCH

	-- SAFETY
	return -99

-- END OF STORE PROCEDURE.
END
GO
USE [master]
GO
ALTER DATABASE [DB_FIXED_ASSET] SET  READ_WRITE 
GO
