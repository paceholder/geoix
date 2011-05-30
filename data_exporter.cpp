#include "data_exporter.h"


#include <QtCore>
#include <QFileDialog>
#include <QApplication>

#include "surface_data.h"

bool gxDataExporter::exportPointsData(gxPoint3DList* data)
{
    Q_UNUSED(data);

    QStringList list;
    return false;
}


//    for I := 0 to XCount - 1 do begin
//      if Assigned(Progress) then Progress(Data, 0, I, XCount);
//      for J := YCount - 1 downto 0 do begin
////        Str(GetSurfaZByIndex(Surfacer, J * XCount + I):15:4, S1); S := S + S1;
//        Str(GetSurfaZByIndex(Surfacer, J * XCount + I):14:4, S1); S := S + ' ' + S1; // <- 15072010
//        Inc(N); if N >= 5 then begin List.Add(S); S := ''; N := 0 end;
//      end;
//      if Length(S) > 0 then begin List.Add(S); S := ''; N := 0 end;
//    end;
//    List.SaveToFile(FileName);
//  finally
//    List.Free
//  end;
//  Result := 0
//end;


bool gxDataExporter::exportSurfaceData(gxSurfaceData* data)
{
    if (!data) return false;

    QStringList list;

    list << "!  GEOIX" << "\n";
    list << "!  SURFACE FILE" << "\n";
    list << "@Surf_Zmap HEADER                     ,      GRID,       5" << "\n";
    list << "      15," + QString::number(data->getNullValue()) + ", , 4, 1" << "\n";
    list << QString("%1, %2, %3, %4, %5, %6").arg(QString::number(data->nY()),
                                                  QString::number(data->nX()),
                                                  QString::number(data->getSize().getMinX()),
                                                  QString::number(data->getSize().getMaxX()),
                                                  QString::number(data->getSize().getMinY()),
                                                  QString::number(data->getSize().getMaxY()))  << "\n";

    list << "         0.0000,         0.0000,         0.0000" << "\n";
    list << "@" << "\n";
    list << "+ Grid data starts after this line" << "\n";

    int n = 0;
    QString s;
    for(int i = 0; i < data->nX(); ++i)
        for(int j = data->nY()-1; j >= 0; --j)
        {
            s += " " + QString::number(-data->at(i, j));
            ++n;
            if (n > 5)
            {
                list << s << "\n";
                s.clear();
                n = 0;
            }
        }

    saveToTextFile(list);

    return true;
}

bool gxDataExporter::exportLinesData(gxContourList* data)
{
    Q_UNUSED(data);
    return false;
}

void gxDataExporter::saveToTextFile(QStringList &list)
{
    QString fileName = QFileDialog::getSaveFileName(0,
                                                    QObject::tr("Save File"),
                                                    QApplication::applicationDirPath(),
                                                    QObject::tr("Text Files (*)"));

    if (fileName.isEmpty()) return;

    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) return;

    QTextStream in(&file);
    foreach(QString line, list)
        in << line;
}
