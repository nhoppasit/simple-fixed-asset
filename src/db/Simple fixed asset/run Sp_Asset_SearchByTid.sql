USE [DB_FIXED_ASSET]
GO

DECLARE	@return_value int,
		@RowCount int,
		@MessageResult nvarchar(200)

EXEC	@return_value = [dbo].[Sp_Asset_SearchByTid]
		@TID = '456',
		@RowCount = @RowCount OUTPUT,
		@MessageResult = @MessageResult OUTPUT

SELECT	@RowCount as N'@RowCount',
		@MessageResult as N'@MessageResult'

SELECT	'Return Value' = @return_value

select * from TB_ASSET

GO
